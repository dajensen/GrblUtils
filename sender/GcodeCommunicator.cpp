#include <string>
#include <memory>
#include <vector>
#include <regex>

#include "log.h"
#include "Utils.h"
#include "CircularBuffer.h"
#include "SerialDataIo.h"
#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"
#include "GrblCommunicator.h"
#include "GcodeCommunicator.h"

#define RISKY_SENDER

bool GcodeCommunicator::SendLine(std::string str) {
    bool rv = false;
    std::regex space_and_comments("\\s|\\(.*?\\)");
    std::string to_send = std::regex_replace(str, space_and_comments, "") + "\n";

    // You can only send this line right now if there's enough space in the controller's receive buffer
    //    Add up all of the values in cb.  If the total plus this string is less than 128, then we can send it.
    //    Put the length of to_send into cb
    int bytes_to_send = to_send.length();
    //    log(DEBUG, "bytes_to_send: " + std::to_string(bytes_to_send));
#ifdef RISKY_SENDER
    if(buffer_used + bytes_to_send < 128) {                     // This one failed until I started stripping out space and comments.
#else
    if(buffer_used == 0) {                                      // This is the non-risky approach
#endif
        log(TO_GRBL, to_send);
        int sendlen = io.Write((uint8_t *)to_send.c_str(), to_send.length());
        cb.put(sendlen);
        buffer_used += sendlen;
        rv = sendlen == bytes_to_send;
    //    log(DEBUG, "+Bytes: " + std::to_string(sendlen));
    //    log(DEBUG, "Bytes in buffer: " + std::to_string(buffer_used));

        lines_sent++;
        if(!rv) {
            log(DEBUG, "ERROR: WE WERE UNABLE TO SEND THE WHOLE MESSAGE");
        }
    }
    else {
    //    log(DEBUG, "DELAYING");
        delay(50);
    }

    return rv;
}

bool GcodeCommunicator::MarkLineReceived() {
    bool rv = false;
    int bytes_acked = cb.get();
    buffer_used -= bytes_acked;
//    log(DEBUG, "-Bytes: " + std::to_string(bytes_acked));
//    log(DEBUG, "Bytes in buffer: " + std::to_string(buffer_used));
    lines_acked++;
    return rv;
}
