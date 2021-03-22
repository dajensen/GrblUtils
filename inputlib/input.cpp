#include <stdlib.h>
#include <string>
#include <vector>
#include <optional>
#include "log.h"
#include "Utils.h"
#include "input.h"
#include "gamepad.h"
#include "keyboard.h"

#define USE_GAMEPAD


Input *Input::CreateInstance() {
#ifdef USE_GAMEPAD
    Gamepad *pGamepad = new Gamepad();
    if(pGamepad->IsValid())
        return (Input *)pGamepad;
#endif
    return new Keyboard(Keyboard::DEFAULT_INITIAL_INCREMENT);
}

