#include <string>
#include "AxisNames.h"

std::string NameToString(AxisNames axis) {
    switch(axis) {
    case X:
        return "X";
    case Y:
        return "Y";
    case Z:
        return "Z";
    case A:
        return "A";
    case B:
        return "B";
    default:
        return "";
    }
}
