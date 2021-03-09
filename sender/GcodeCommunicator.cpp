#include <string>
#include <memory>
#include <vector>

#include "log.h"
#include "Utils.h"
#include "CircularBuffer.h"
#include "SerialDataIo.h"
#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"
#include "GrblCommunicator.h"
#include "GcodeCommunicator.h"


bool GcodeCommunicator::SendLine(std::string str) {
    bool rv = false;
    std::string to_send = str + "\n"; 

// You can only do this if there's enough space in the controller's receive buffer
//    Add up all of the values in cb.  If the total plus this string is less than 128, then we can send it.
//    Put the length of to_send into cb
    int bytes_to_send = to_send.length();
    if(buffer_used + bytes_to_send < GRBL_RX_BUFFER_SIZE) {
        log(TO_GRBL, to_send);
        int sendlen = io.Write((uint8_t *)to_send.c_str(), to_send.length());
        cb.put(sendlen);
        buffer_used += sendlen;
        rv = sendlen == bytes_to_send;
//        log(DEBUG, "+Bytes: " + std::to_string(sendlen));
//        log(DEBUG, "Bytes in buffer: " + std::to_string(buffer_used));
    }

    return rv;
}

bool GcodeCommunicator::MarkLineReceived() {
    bool rv = false;
    int bytes_acked = cb.get();
    buffer_used -= bytes_acked;
//    log(DEBUG, "-Bytes: " + std::to_string(bytes_acked));
//    log(DEBUG, "Bytes in buffer: " + std::to_string(buffer_used));
    return rv;
}
