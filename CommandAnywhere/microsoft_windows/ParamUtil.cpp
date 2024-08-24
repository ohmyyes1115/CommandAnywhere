#include "ParamUtil.h"

// public static
MouseState ParamUtil::GetMouseState(WPARAM wParam, LPARAM lParam) {
    return MouseState{
        .leftButtonPressed   = IsLeftButtonPressed  (wParam),
        .rightButtonPressed  = IsRightButtonPressed (wParam),
        .middleButtonPressed = IsMiddleButtonPressed(lParam),
        .cursorLocation      = GetCursorLocation    (lParam),
    };
}

// public static
CursorLocation ParamUtil::GetCursorLocation(LPARAM lParam) {
    return { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
}

// public static
bool ParamUtil::IsLeftButtonPressed(WPARAM wParam) {
    return wParam & MK_LBUTTON;
}

// public static
bool ParamUtil::IsRightButtonPressed(WPARAM wParam) {
    return wParam & MK_RBUTTON;
}

// public static
bool ParamUtil::IsMiddleButtonPressed(LPARAM wParam) {
    return wParam & MK_MBUTTON;
}
