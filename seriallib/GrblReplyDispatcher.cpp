#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <string>
#include <memory>
#include <vector>

#include "log.h"
#include "Utils.h"
#include "SerialDataIo.h"
#include "AxisNames.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"


void GrblReplyDispatcher::DispatchGrblReply(std::string s) {
    std::string trimmed = ltrim(s, WHITESPACE);
//    if(!trimmed.empty()) {
        for(auto &r : dispatch_info) {
            if(r.Recognized(trimmed)){
                auto message = r.CreateInstance(trimmed);
                r.listener.HandleMessage(*message);
            }
        }
//    }
}

void GrblReplyDispatcher::RegisterMessageType(GrblReply::recognized_fn recognized, GrblReply::createinstance_fn createinstance, GrblListener &listener){
    dispatch_info.emplace_back(recognized, createinstance, listener);
}
