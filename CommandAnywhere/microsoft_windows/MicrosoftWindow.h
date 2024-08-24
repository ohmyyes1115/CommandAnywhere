#pragma once
#include "IDrawer.h"
#include "MicrosoftInnerWindow.h"
#include "MicrosoftWindowsUtil.h"
#include "MouseState.h"
#include "IEvtListener.h"

#include <windows.h>
#include <string>
#include <windowsx.h>

class MicrosoftWindow {
public:
    MicrosoftWindow(HINSTANCE hInstance, const std::wstring& className, IEvtListener* evtListener, IDrawer* drawer);

    ~MicrosoftWindow();

    void show();

    void hide();

    void requestRedraw();

    void setPosition(int left, int top);

    void setSize(int width, int height);

    bool isVisible() const;

private:
    void doRedraw();

    void onPaint();

    // [high-level] mouse > L-button > clicked
    void onMouse_LeftButton_Clicked(const MouseState& mouseState);

    // [high-level] mouse > L-button > double-clicked
    void onMouse_LeftButton_DoubleClicked(const MouseState& mouseState);

    // [low-level] mouse > L-button > down
    void onMouse_LeftButton_Down(const MouseState& mouseState);

    // [low-level] mouse > L-button > up
    void onMouse_LeftButton_UP(const MouseState& mouseState);

    // [low-level] mouse > L-button > drag > begun
    void onMouse_LeftButtonDrag_Begun(const MouseState& mouseState);

    // [low-level] mouse > L-button > drag > on-going
    void onMouse_LeftButtonDrag_Ing(const MouseState& mouseState);

    // [low-level] mouse > L-button > drag > finished
    void onMouse_LeftButtonDrag_Finished();

    // [high-level] mouse > R-button > clicked
    void onMouse_RightButton_Clicked(const MouseState& mouseState);

    // [high-level] mouse > R-button > double-clicked
    void onMouse_RightButton_DoubleClicked(const MouseState& mouseState);

    // [low-level] mouse > R-button > down
    void onMouse_RightButton_Down(const MouseState& mouseState);

    // [low-level] mouse > R-button > up
    void onMouse_RightButton_UP(const MouseState& mouseState);

    // [low-level] mouse > R-button > drag > begun
    void onMouse_RightButtonDrag_Begun(const MouseState& mouseState);

    // [low-level] mouse > R-button > drag > on-going
    void onMouse_RightButtonDrag_Ing(const MouseState& mouseState);

    // [low-level] mouse > R-button > drag > finished
    void onMouse_RightButtonDrag_Finished();

    // [low-level] mouse > wheel
    void onMouse_Wheel(HWND hwnd, WPARAM wParam, LPARAM lParam);

    // [high-level] mouse > hover
    void onMouse_Hover(const MouseState& mouseState);

    // [low-level] mouse > moving
    void onMouse_Moving(HWND hwnd, const MouseState& mouseState);

    // [low-level] window position > changed
    void onWindowPos_Changed();

    static LRESULT CALLBACK HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static void SetParentPointer(HWND hwnd, void* parent);

    static MicrosoftWindow* GetParentPointer(HWND hwnd);

    HINSTANCE mhInstance = nullptr;

    std::wstring mClassName;

    bool mIsVisible = false;

    bool mIsDragging = false;

    bool mIsMouseLButtonDown = false;

    IEvtListener* mEvtListener = nullptr;

    IDrawer* mDrawer = nullptr;

    MicrosoftInnerWindow mInnerWindow;
};

