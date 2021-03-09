#include <string>
#include <vector>
#include <memory>

#include "log.h"
#include "Utils.h"
#include "AxisNames.h"
#include "GrblReply.h"
#include "Status.h"

double StatusReply::workspace_offsets[AxisNames::NUM_AXES];
