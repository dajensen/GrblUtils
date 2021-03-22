#ifndef __LOG_H
#define __LOG_H

enum LogMessageType {
    TO_GRBL,
    FROM_GRBL,
    DEBUG
};

typedef void (*logfn)(LogMessageType lmt, std::string msg);

extern void SetLogFn(logfn);
extern void log(LogMessageType lmt, std::string msg);
extern void logDumpData(uint8_t *data, int len);
extern void log_printf(LogMessageType lmt, const char *fmt, ...);

#endif  // __LOG_H