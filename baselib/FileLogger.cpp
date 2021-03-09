#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <vector>

#include "log.h"
#include "Utils.h"
#include "FileLogger.h"

FileLogger *FileLogger::pInstance = NULL;

FileLogger::FileLogger(std::string filename){
    fname = filename;
}

void FileLogger::AddString(LogMessageType lmt, std::string str){
    std::string to_write = trim(str, WHITESPACE) + "\n";
    fd = open(fname.c_str(), O_APPEND | O_WRONLY);
    ssize_t rv = write(fd, to_write.c_str(), to_write.length());
    close(fd);
}

FileLogger *FileLogger::GetInstance(std::string filename){
    if(!pInstance)
        pInstance = new FileLogger(filename);
    return pInstance;
}
