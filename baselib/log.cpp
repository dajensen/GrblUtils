#include "stdlib.h"
#include "stdarg.h"
#include <string>
#include <vector>
#include "Utils.h"
#include "log.h"

logfn LogFn = NULL;

void SetLogFn(logfn fn) {
    LogFn = fn;
}

void log(LogMessageType lmt, std::string msg) {
    if(LogFn) {
        LogFn(lmt, msg);
    }
    else
        printf("Could not log message: %s\n", msg.c_str());
}

void logDumpData(uint8_t *data, int len){
    std::string str("\n");

    for(int i = 0; i < len; i++) {
        if(i % 16 == 0){
            str += ("\n");
        }
        else if(i % 8 == 0){
            str += "   ";
        }
        str += " " + to_hexstring(data[i]);
    }
    log(DEBUG, str + "\n");
}

void log_printf(LogMessageType lmt, const char *fmt, ...){
    char msg[256];      // Must be big enough.  Don't overrun this.

    va_list args;
    va_start (args, fmt);
    vsprintf (msg, fmt, args);
    log(lmt, msg);
    va_end (args);
}
