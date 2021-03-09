#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>

#include "log.h"
#include "Utils.h"
#include "DoubleObserver.h"
#include "AxisNames.h"
#include "SerialDataIo.h"

#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"
#include "GrblCommunicator.h"

#include "Replies/Status.h"
#include "Requests/JogMessage.h"
#include "Requests/OriginMessage.h"

#include "axis.h"
#include "valuedisplay.h"
#include "axisreport.h"
#include "toppanel.h"


void TopPanel::HandleMessage(GrblReply &msg){

    GrblReply *pReply = &msg;
    StatusReply *pStatusReply = (StatusReply *)pReply;
    for(int i = 0; i < actuals.size(); i++){
        double val = pStatusReply->GetWorkspaceCoordinates((AxisNames)i);
        actuals[i].ChangeTo(val);
    }
    for(int i = 0; i < machines.size(); i++){
        double val = pStatusReply->GetMachineCoordinates((AxisNames)i);
        machines[i].ChangeTo(val);
    }
}

void TopPanel::SetAxes(std::vector<Axis> &axis) {
    int col = (screencols - (axis.size() * AxisReport::WIN_WIDTH)) / 2;
    for(int i = 0; i < axis.size(); i++) {
        axisreports.push_back(new AxisReport(stdscr, NameToString((AxisNames)i), COLOR_PAIR(1), 0, col));
        col += AxisReport::WIN_WIDTH;
        AxisReport *report = axisreports.back();
        axis[i].RegisterObserver(std::shared_ptr<DoubleObserver>(report));

        workspaces.emplace_back(0.0);
        DoubleObservable &ws = workspaces.back();
        std::shared_ptr<DoubleObserver> ws_obs = report->GetWorkspaceObserver();
        if(ws_obs)
            ws.RegisterObserver(ws_obs);

        actuals.emplace_back(0.0);
        DoubleObservable &actual = actuals.back();
        std::shared_ptr<DoubleObserver> actual_obs = report->GetActualObserver();
        if(actual_obs)
            actual.RegisterObserver(actual_obs);

        machines.emplace_back(0.0);
        DoubleObservable &machine = machines.back();
        std::shared_ptr<DoubleObserver> mach_obs = report->GetMachineObserver();
        if(mach_obs)
            machine.RegisterObserver(mach_obs);
    }
}
