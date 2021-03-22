#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <ncurses.h>
#include <signal.h>

#include <time.h>
#include <string>
#include <memory>
#include <utility>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>

#include <sys/ioctl.h>
#include "Utils.h"
#include "log.h"
#include "CircularBuffer.h"
#include "FileLogger.h"
#include "AxisNames.h"
#include "SerialDataIo.h"

#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"
#include "GrblCommunicator.h"
#include "GcodeCommunicator.h"

#include "Requests/WelcomeMessage.h"
#include "Requests/StatusQueryMessage.h"
#include "Replies/Empty.h"
#include "Replies/Welcome.h"
#include "Replies/Status.h"

#include "screen.h"
#include "input.h"
#include "keyboard.h"
#include "OutputWindow.h"
#include "EmptyListener.h"
#include "StatusListener.h"
#include "LineReader.h"

bool get_options(int argc, char *argv[], std::string &portname, std::string &filename) {
    bool rv = false;
    int c;

     while ((c = getopt (argc, argv, "f:p:")) != -1) {
        switch (c)
        {
            case 'f':
                filename = optarg;
                break;
            case 'p':
                portname = optarg;
                break;
        }
     }

    if(portname.length() > 0 && filename.length() > 0)
        rv = true;

    return rv;
}


GcodeCommunicator *pCommunicatorToShutDown = NULL;
void finish(int sig) {
    Screen::finish(sig);
    if(pCommunicatorToShutDown)
        pCommunicatorToShutDown->SendByte(0x18);
    exit(0);
}


void RegisterForSigInt(GcodeCommunicator &comm) {
    struct sigaction sa;

    // Save a pointer so we can use it to send an emergency shutdown.
    pCommunicatorToShutDown = &comm;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = finish;
    sigaction(SIGINT, &sa, NULL);
}


void LogFn(LogMessageType lmt, std::string msg) {
    FileLogger::Log(lmt, msg);
    OutputWindow::Log(lmt, msg);    
}

bool WaitForFlag(GcodeCommunicator &comm, bool &flag, unsigned long timeout) {
    unsigned long start = millis();
    while(flag == false && millis() - start < timeout) {
        comm.CheckIncomingMessages();
        delay(10);
    }
    return flag;
}

int main(int argc, char *argv[]){

    FileLogger *flogger = FileLogger::GetInstance("logfile.txt");
    SetLogFn(LogFn);
    log(DEBUG, "************************ SENDER LOG BEGINS ************************");

    printf("Checking options\n");
    std::string port_name;
    std::string file_name;
    if(!get_options(argc, argv, port_name, file_name)){
        printf("usage: sender -f filename -p portname\n");
        exit(-1);
    }

    LineReader gcreader(file_name);
    if(!gcreader.IsOpen()) {
        printf("Unable to open file %s\n", file_name.c_str());
        exit(-1);
    }

    printf("Connecting serial port\n");
    SerialDataIoImpl SerialDataIo;
    if(!SerialDataIo.begin(port_name)) {
        printf("Unable to open serial port %s\n", port_name.c_str());
        exit(-1);
    }

    GrblReplyDispatcher dispatcher;
    GcodeCommunicator comm(SerialDataIo, dispatcher);
    RegisterForSigInt(comm);

    delay(1000);

    std::shared_ptr<Screen::ReinitNotifier> screen_notifier = std::make_shared<Screen::ReinitNotifier>();
    Screen screen(screen_notifier);
    OutputWindow *pOutputWin = OutputWindow::GetInstance(stdscr, "Output", COLOR_PAIR(3), 0, 0, screen.GetCols(), screen.GetRows());
    Input *pInput = Input::CreateInstance();

    bool status_received = false;
    StatusListener statuslistener(status_received);
    dispatcher.RegisterMessageType(StatusReply::Recognized, StatusReply::CreateInstance, statuslistener);

    EmptyListener emptylistener(comm);
    dispatcher.RegisterMessageType(EmptyReply::Recognized, EmptyReply::CreateInstance, emptylistener);

    WelcomeMessage welcome;
    comm.SendRequest(welcome);

    delay(200);
    StatusQueryMessage query;
    comm.SendRequest(query);

    if(!WaitForFlag(comm, status_received, 10000)) {
        log(DEBUG, "Never received a status response, so gave up.");
        screen.Restore();
        exit(-1);
    }

    std::string gcode_line;
    bool data_to_send = gcreader.ReadLine(gcode_line);
    while(data_to_send) {

        comm.CheckIncomingMessages();

        if(comm.SendLine(gcode_line))
            data_to_send = gcreader.ReadLine(gcode_line);
        else
            delay(100);
    }

    screen.Restore();
}
