#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>

#include "log.h"
#include "Utils.h"
#include "CircularBuffer.h"
#include "DoubleObserver.h"
#include "AxisNames.h"
#include "SerialDataIo.h"

#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"
#include "GrblCommunicator.h"
#include "GcodeCommunicator.h"

#include "Replies/Empty.h"
#include "EmptyListener.h"

void EmptyListener::HandleMessage(GrblReply &msg){
    GrblReply *pReply = &msg;
    EmptyReply *pEmpty = (EmptyReply *)pReply;
    comm.MarkLineReceived();
}
