#pragma once
#include "MicrosoftWindow.h"
#include "MouseState.h"
#include <Windows.h>

class ParamUtil
{
public:
    ParamUtil() = delete;

    static MouseState GetMouseState(WPARAM wParam, LPARAM lParam);

    static CursorLocation GetCursorLocation(LPARAM lParam);

    static bool IsLeftButtonPressed(WPARAM wlParam);

    static bool IsRightButtonPressed(WPARAM wlParam);

    static bool IsMiddleButtonPressed(LPARAM lParam);
};

