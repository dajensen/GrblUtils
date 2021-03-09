#include <string>
#include <memory>
#include <utility>
#include <array>
#include <vector>

#include "log.h"
#include "Utils.h"
#include "DoubleObserver.h"
#include "AxisNames.h"
#include "SerialDataIo.h"

#include "GrblRequest.h"
#include "GrblReply.h"
#include "GrblCommunicator.h"
#include "Requests/JogMessage.h"
#include "Requests/OriginMessage.h"

#include "axis.h"


// Now that all of the axis functionality is in a DoubleObservable, we probably could just delete the class. 