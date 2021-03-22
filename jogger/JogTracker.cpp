#include <stdlib.h>
#include <string>
#include <vector>
#include <memory>
#include <optional>

#include "log.h"
#include "Utils.h"
#include "DoubleObserver.h"
#include "AxisNames.h"
#include "SerialDataIo.h"

#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblCommunicator.h"

#include "Replies/Status.h"
#include "Requests/JogMessage.h"
#include "Requests/OriginMessage.h"

#include "axis.h"
#include "JogTracker.h"


void JogTracker::JogWatcher::DataObserved(double val){
//    log(DEBUG, "JogWatcher saw a change");
    SetJogState(val);
    tracker.CheckForChanges();
}

JogTracker::JogTracker(GrblCommunicator &comm) : comm(comm), waiting_for_grbl(false), feedrate(4000) {
}

void JogTracker::HandleMessage(GrblReply &msg){
//    log(DEBUG, "JogTracker got a message");
    waiting_for_grbl = false;
    CheckForChanges();
}

void JogTracker::CheckForChanges() {
//    log(DEBUG, "CheckForChanges");
    if(!waiting_for_grbl) {
        std::vector<std::string> axisstrings;

        bool changed = false;
        for(auto watcher : jogwatchers) {
            if(watcher->IsChanged()){
                changed = true;
                axisstrings.push_back(watcher->GetString());
            }
        }
        if(changed) {
            SendJogMessage(axisstrings);
            for(auto watcher : jogwatchers) {
                watcher->ClearJogState();
            }
        }
    }
}

void JogTracker::SendJogMessage(std::vector<std::string> &axisstrings) {

    JogMessage jog(axisstrings, 4000);
    comm.SendRequest(jog);

    waiting_for_grbl = true;
}

void JogTracker::SetAxis(AxisNames axis_name, DoubleObservable &axis){
    std::shared_ptr<JogWatcher> sp = std::make_shared<JogWatcher>(NameToString(axis_name), *this);
    jogwatchers.push_back(sp);
    axis.RegisterObserver(sp);
}
