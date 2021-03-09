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
#include "StatusListener.h"

void StatusListener::HandleMessage(GrblReply &msg){
    GrblReply *pReply = &msg;
    StatusReply *pStatusReply = (StatusReply *)pReply;
    log(DEBUG, pStatusReply->GetStatus());
//    planner_slots_free = pStatusReply->GetPlannerSlotsFree();
//    log(DEBUG, "Planner slots free: " + std::to_string(planner_slots_free));
    flag = true;
}
