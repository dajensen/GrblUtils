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
#include "InitStatusListener.h"

void InitStatusListener::HandleMessage(GrblReply &msg){
    log(DEBUG, "Got a message");
    GrblReply *pReply = &msg;
    StatusReply *pStatusReply = (StatusReply *)pReply;
    for(int i = 0; i < sizeof(vals) / sizeof(vals[0]); i++){
        vals[i] = pStatusReply->GetWorkspaceCoordinates((AxisNames)i);
    }
    done = true;
}

double InitStatusListener::GetValue(int i) {
    if(i > 0 && i < AxisNames::NUM_AXES)
        return vals[i];
    return 0.0;
}
