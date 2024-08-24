#pragma once
#include "MicrosoftWindowsUtil.h"

class IEvtListener {
public:
    virtual ~IEvtListener() = default;

    // [high-level] mouse > L-button > clicked / double-clicked
    virtual void onMouse_LeftButton_Clicked(const CursorLocation& cursorLocation) {}
    virtual void onMouse_LeftButton_DoubleClicked(const CursorLocation& cursorLocation) {}

    // [low-level] mouse > L-button > down / up
    virtual void onMouse_LeftButton_Down(const CursorLocation& cursorLocation) {}
    virtual void onMouse_LeftButton_UP(const CursorLocation& cursorLocation) {}

    // [low-level] mouse > L-button > drag > begun / on-going / finished
    virtual void onMouse_LeftButtonDrag_Begun(const CursorLocation& cursorLocation) {}
    virtual void onMouse_LeftButtonDrag_Ing(const CursorLocation& cursorLocation) {}
    virtual void onMouse_LeftButtonDrag_Finished() {}

    // [high-level] mouse > R-button > clicked / double-clicked
    virtual void onMouse_RightButton_Clicked(const CursorLocation& cursorLocation) {}
    virtual void onMouse_RightButton_DoubleClicked(const CursorLocation& cursorLocation) {}

    // [low-level] mouse > R-button > down / up
    virtual void onMouse_RightButton_Down(const CursorLocation& cursorLocation) {}
    virtual void onMouse_RightButton_UP(const CursorLocation& cursorLocation) {}

    // [low-level] mouse > R-button > drag > begun / on-going / finished
    virtual void onMouse_RightButtonDrag_Begun(const CursorLocation& cursorLocation) {}
    virtual void onMouse_RightButtonDrag_Ing(const CursorLocation& cursorLocation) {}
    virtual void onMouse_RightButtonDrag_Finished() {}

    // [low-level] mouse > wheel
    virtual void onMouse_Wheel(HWND hwnd, WPARAM wParam, LPARAM lParam) {}

    // [high-level] mouse > hover
    virtual void onMouse_Hover(const CursorLocation& cursorLocation) {}
};

