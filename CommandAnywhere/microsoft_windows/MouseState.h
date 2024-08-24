#pragma once
#include "MicrosoftWindowsUtil.h"

struct MouseState {
    // button states
    bool leftButtonPressed = false;
    bool rightButtonPressed = false;
    bool middleButtonPressed = false;

    // cursor states
    CursorLocation cursorLocation;

    // wheel states
    // TODO:
};
