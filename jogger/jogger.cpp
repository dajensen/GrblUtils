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
#include "Replies/Empty.h"

#include "DoubleObserver.h"
#include "axis.h"
#include "valuedisplay.h"
#include "axisreport.h"
#include "InitStatusListener.h"
#include "toppanel.h"
#include "screen.h"
#include "input.h"
#include "keyboard.h"
#include "OutputWindow.h"
#include "JogTracker.h"


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

void UpdateAxes(Input::Changes changes, std::vector<Axis> &axis) {
    if(changes.x){
        axis[X].ChangeBy(changes.x);
    }
    if(changes.y){
        axis[Y].ChangeBy(changes.y);
    }
    if(changes.z){
        axis[Z].ChangeBy(changes.z);
    }
    if(changes.a){
        axis[A].ChangeBy(changes.a);
    }
    if(changes.b){
        axis[B].ChangeBy(changes.b);
    }
    if(changes.events & INPUT_X_ZERO) {
        log(DEBUG, "ZERO X");
        axis[X].SetZero();
    }
    if(changes.events & INPUT_X_GOTO) {
        log(DEBUG, "GOTO X");
        axis[X].ChangeTo(0.0);
    }
    if(changes.events & INPUT_Y_ZERO) {
        axis[Y].SetZero();
    }
    if(changes.events & INPUT_Y_GOTO) {
        axis[Y].ChangeTo(0.0);
    }
    if(changes.events & INPUT_Z_ZERO) {
        axis[Z].SetZero();
    }
    if(changes.events & INPUT_Z_GOTO) {
        axis[Z].ChangeTo(0.0);
    }
    if(changes.events & INPUT_A_ZERO) {
        axis[A].SetZero();
    }
    if(changes.events & INPUT_A_GOTO) {
        axis[A].ChangeTo(0.0);
    }
    if(changes.events & INPUT_B_ZERO) {
        axis[B].SetZero();
    }
    if(changes.events & INPUT_B_GOTO) {
        axis[B].ChangeTo(0.0);
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
    Input *pInput = Input::CreateInstance();
 
    WelcomeMessage welcome;
    comm.SendRequest(welcome);

    StatusQueryMessage query;
    comm.SendRequest(query);

    // An array of Axis objects.  They hold the values of each axis and are observable.
    std::vector<Axis> axis;
    for(int i = 0; i < AxisNames::NUM_AXES; i++){
        axis.emplace_back(NameToString((AxisNames)i), comm);
    }

    TopPanel toppanel(stdscr, COLOR_PAIR(2), 0, 0, screen.GetCols());
    toppanel.SetAxes(axis);
    dispatcher.RegisterMessageType(StatusReply::Recognized, StatusReply::CreateInstance, toppanel);

    JogTracker jogtracker(comm);
    for(int i = 0; i < AxisNames::NUM_AXES; i++){
        jogtracker.SetAxis((AxisNames)i, *(DoubleObservable *)&axis[i]);
    }
    dispatcher.RegisterMessageType(EmptyReply::Recognized, EmptyReply::CreateInstance, jogtracker);

    // Initialize each axis with the observers in place
    for(int i = 0; i < NUM_AXES; i++){
        axis[i].ChangeTo(initial_values[i]);
    }

    unsigned long last_status_time = millis();
    while(true) {
        Input::Changes changes = pInput->Check();
        UpdateAxes(changes, axis);

        comm.CheckIncomingMessages();

        // Delay until a bit of time has passed - probably don't need to check these things more than every 10 to 100 ms.
        delay(50);

        if(millis() - last_status_time > 2500){
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
