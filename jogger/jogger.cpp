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

#include <sys/ioctl.h>
#include "Utils.h"
#include "log.h"
#include "FileLogger.h"
#include "AxisNames.h"
#include "SerialDataIo.h"

#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"
#include "GrblCommunicator.h"

#include "Requests/WelcomeMessage.h"
#include "Requests/StatusQueryMessage.h"
#include "Requests/JogMessage.h"
#include "Requests/OriginMessage.h"
#include "Replies/Welcome.h"
#include "Replies/Status.h"

#include "DoubleObserver.h"
#include "axis.h"
#include "valuedisplay.h"
#include "axisreport.h"
#include "InitStatusListener.h"
#include "toppanel.h"
#include "screen.h"
#include "keyboard.h"
#include "OutputWindow.h"



bool get_options(int argc, char *argv[], std::string &portname) {
    bool rv = false;
    int c;

     while ((c = getopt (argc, argv, "p:")) != -1) {
        switch (c)
        {
            case 'p':
                portname = optarg;
            break;
        }
     }

    if(portname.length() > 0)
        rv = true;

    return rv;
}


double increment = 1.0;

void UpdateAxes(uint32_t kbmask, std::vector<Axis> &axis) {
    if(kbmask & KB_X_INC){
        axis[X].MoveBy(increment);
    }
    if(kbmask & KB_X_DEC){
        axis[X].MoveBy(-increment);
    }
    if(kbmask & KB_X_ZERO) {
        axis[X].Zero();
    }
    if(kbmask & KB_X_GOTO) {
        axis[X].GotoZero();
    }
    if(kbmask & KB_Y_INC){
        axis[Y].MoveBy(increment);
    }
    if(kbmask & KB_Y_DEC){
        axis[Y].MoveBy(-increment);
    }
    if(kbmask & KB_Y_ZERO) {
        axis[Y].Zero();
    }
    if(kbmask & KB_Y_GOTO) {
        axis[Y].GotoZero();
    }
    if(kbmask & KB_Z_INC){
        axis[Z].MoveBy(increment);
    }
    if(kbmask & KB_Z_DEC){
        axis[Z].MoveBy(-increment);
    }
    if(kbmask & KB_Z_ZERO) {
        axis[Z].Zero();
    }
    if(kbmask & KB_Z_GOTO) {
        axis[Z].GotoZero();
    }
    if(kbmask & KB_A_INC){
        axis[A].MoveBy(increment);
    }
    if(kbmask & KB_A_DEC){
        axis[A].MoveBy(-increment);
    }
    if(kbmask & KB_A_ZERO) {
        axis[A].Zero();
    }
    if(kbmask & KB_A_GOTO) {
        axis[A].GotoZero();
    }
    if(kbmask & KB_B_INC){
        axis[B].MoveBy(increment);
    }
    if(kbmask & KB_B_DEC){
        axis[B].MoveBy(-increment);
    }
    if(kbmask & KB_B_ZERO) {
        axis[B].Zero();
    }
    if(kbmask & KB_B_GOTO) {
        axis[B].GotoZero();
    }
    if(kbmask & KB_INC_INCREMENT){
        if(increment < 100) {
            increment *= 10;
        }
    }
    if(kbmask & KB_INC_DECREMENT){
        if(increment > 0.001) {
            increment /= 10;
        }
    }
}

void LogFn(LogMessageType lmt, std::string msg) {
    FileLogger::Log(lmt, msg);
    OutputWindow::Log(lmt, msg);    
}

const int INIT_TIMEOUT = 5000;
bool GetInitialValues(SerialDataIoImpl &serial, double *vals) {
    bool rv = false;

    // You MUST delay for a second here.  Failing to do so will cause Grbl to (sometimes) fail to respond.
    delay(1000);

    GrblReplyDispatcher dispatcher;
    GrblCommunicator comm(serial, dispatcher);

    WelcomeMessage welcome;
    comm.SendRequest(welcome);

    InitStatusListener initstatus;
    dispatcher.RegisterMessageType(StatusReply::Recognized, StatusReply::CreateInstance, initstatus);

    unsigned long start = millis();
    while(!initstatus.HaveInitialStatus() && millis() - start < INIT_TIMEOUT) {
        comm.CheckIncomingMessages();
        delay(250);
        StatusQueryMessage query;
        comm.SendRequest(query);
    }
    if(initstatus.HaveInitialStatus()) {
        for(int i = 0; i < AxisNames::NUM_AXES; i++) {
            vals[i] = initstatus.GetValue((AxisNames)i);
        }
        rv = true;
    }
    return rv;
}

int main(int argc, char *argv[]){

    FileLogger *flogger = FileLogger::GetInstance("logfile.txt");
    SetLogFn(LogFn);
    log(DEBUG, "************************ JOGGER LOG BEGINS ************************");

    printf("Checking options\n");
    std::string port_name;
    if(!get_options(argc, argv, port_name)){
        printf("usage: jogger -p portname\n");
        exit(-1);
    }

    printf("Connecting serial port\n");
    SerialDataIoImpl SerialDataIo;
    if(!SerialDataIo.begin(port_name)) {
        printf("Unable to open serial port %s\n", port_name.c_str());
        exit(-1);
    }

    printf("Getting initial settings from Grbl\n");
    double initial_values[AxisNames::NUM_AXES];
    if(!GetInitialValues(SerialDataIo, initial_values)) {
        printf("Unable to get initial values\n");
        exit(-1);
    }

    GrblReplyDispatcher dispatcher;
    GrblCommunicator comm(SerialDataIo, dispatcher);

    std::shared_ptr<Screen::ReinitNotifier> screen_notifier = std::make_shared<Screen::ReinitNotifier>();
    Screen screen(screen_notifier);

    OutputWindow *pOutputWin = OutputWindow::GetInstance(stdscr, "Output", COLOR_PAIR(3), 
                                        AxisReport::WIN_HEIGHT, 0, screen.GetCols(), screen.GetRows() - AxisReport::WIN_HEIGHT);
    Keyboard keyboard;
    WelcomeMessage welcome;
    comm.SendRequest(welcome);

    StatusQueryMessage query;
    comm.SendRequest(query);

    TopPanel toppanel(stdscr, COLOR_PAIR(2), 0, 0, screen.GetCols());
    dispatcher.RegisterMessageType(StatusReply::Recognized, StatusReply::CreateInstance, toppanel);

    // An array of Axis objects.  They hold the values of each axis and are observable.
    std::vector<Axis> axis;
    for(int i = 0; i < AxisNames::NUM_AXES; i++){
        axis.emplace_back(NameToString((AxisNames)i), comm);
    }
    toppanel.SetAxes(axis);
    // Initialize each axis with the observers in place
    for(int i = 0; i < NUM_AXES; i++){
        axis[i].ChangeTo(initial_values[i]);
    }

    unsigned long last_status_time = millis();
    uint32_t prev_keymask  = 0;
    while(true) {
        uint32_t kbmask = keyboard.Check();
        if(kbmask){
           UpdateAxes(kbmask, axis);
        }
        else {
            if(prev_keymask) {
                // This should do an immediate cancel, but it seems to have side effects, like making future jog messages fail.
                // So don't do it for now.
                // comm.SendByte(0x85);
            }
        }
        prev_keymask = kbmask;

        comm.CheckIncomingMessages();

        // Delay until a bit of time has passed - probably don't need to check these things more than every 10 to 100 ms.
        delay(50);

        if(millis() - last_status_time > 250){
            comm.SendRequest(query);
            last_status_time = millis();
        }

        // DAJ TODO: If the screen size has changed, then we need to recalculate the layout.
//        if(screen_notifier->Get()) {
//            screen.Reinit();
//        }
    }
    screen.Restore();
}
