#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
//#include <errno.h>

#include <string>
#include <memory>
#include <vector>

#include "log.h"
#include "Utils.h"
#include "SerialDataIo.h"
#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"
#include "GrblCommunicator.h"

const char GrblCommunicator::terminator[] = {'o', 'k', '\r', '\n'};
const int GrblCommunicator::terminator_len = sizeof(terminator) / sizeof(terminator[0]);


bool GrblCommunicator::SendRequest(GrblRequest &msg) {
    std::string to_send = msg.write() + "\n"; 
    log(TO_GRBL, to_send);
    int rv = io.Write((uint8_t *)to_send.c_str(), to_send.length());
    return rv;
}

bool GrblCommunicator::SendByte(uint8_t val) {
    int rv = io.Write(&val, 1);
    return rv;
}

void GrblCommunicator::CheckIncomingMessages(){
    int readlen;
    while((readlen = io.Read(&buf[bytes_received], 1)) > 0) {
        uint8_t c = buf[bytes_received++];
//        log(DEBUG, std::string((const char *)&c, 1));
        if(found_terminator(c)) {
//            logDumpData(buf, bytes_received);
            std::string msg = trim(std::string((const char *)buf, bytes_received - terminator_len), WHITESPACE);
            if(msg.length() > 0){
                log(FROM_GRBL, msg + "\n");
            }
            dispatcher.DispatchGrblReply(msg);

            bytes_received = 0;
        }
        if(bytes_received == sizeof(buf)){
            log(DEBUG, "TROUBLE: Incoming message never terminated.");
            bytes_received = 0;
        }
    }
}


bool GrblCommunicator::found_terminator(uint8_t c) {
    static int match_pos = 0;
    bool rv = false;

    if(c == (uint8_t)terminator[match_pos]) {
        match_pos++;
    }
    else {
        match_pos = 0;
    }

    if(match_pos == terminator_len) {
        match_pos = 0;
        rv = true;
    }

    return rv;
}
