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

#include "Utils.h"
#include "SerialDataIo.h"
#include "AxisNames.h"
#include "GrblReply.h"
#include "GrblReplyDispatcher.h"


/*
void GrblReply::RegisterListener(GrblReplyDispatcher &dispatcher, std::unique_ptr<GrblListener> &listener) {
    auto recognizer = std::make_unique<GrblReply::Recognizer>(listener);
    dispatcher.RegisterMessageType(recognizer);
}
*/