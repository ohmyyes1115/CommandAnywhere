#include "MicrosoftInnerWindow.h"
#include <iostream>

using std::wstring;

// public
MicrosoftInnerWindow::MicrosoftInnerWindow(
    int dwStyle,
    int dwExStyle,
    HINSTANCE hInstance,
    const wstring& className,
    const MsWindowEventHandler& eventHandler)

    : mhInstance(hInstance)
    , mClassName(className)
    , mIsLayered(dwExStyle & WS_EX_LAYERED) {

    // TODO: 
    //   1. Use RAII to manage the window handle and Class registration
    //   2. Error handling
    registerClass(eventHandler.wndProc);

    mWinHandle = CreateWindowEx(
        dwExStyle, className.c_str(), L"", dwStyle,
        mWindowPosition.x, mWindowPosition.y,
        mWindowSize.w, mWindowSize.h,
        nullptr, nullptr, hInstance, eventHandler.lpParam);

    if (!mWinHandle) {
        auto res = GetLastError();
        int a = 0;
    }
}

// public
MicrosoftInnerWindow::~MicrosoftInnerWindow() {
    if (DestroyWindow(mWinHandle) || UnregisterClass(mClassName.c_str(), mhInstance)) {
        // TODO: Log
    }
}

// public
bool MicrosoftInnerWindow::show() {
    bool originalVisible = ShowWindow(mWinHandle, SW_SHOWDEFAULT);
    return true;
}

// public
bool MicrosoftInnerWindow::hide() {
    bool originalVisible = ShowWindow(mWinHandle, SW_HIDE);
    return true;
}

// public
bool MicrosoftInnerWindow::setPosition(const WindowPosition& topLeft) {
    return setPosition(topLeft.x, topLeft.y);
}

// public
bool MicrosoftInnerWindow::setPosition(int left, int top) {
    if (SetWindowPos(mWinHandle, HWND_TOPMOST, left, top, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE)) {
        mWindowPosition = { left, top };
        return true;
    }

    return false;
}

// public
WindowPosition MicrosoftInnerWindow::getTopLeft() const {
    return mWindowPosition;
}

// public
WindowPosition MicrosoftInnerWindow::getBottomRight() const {
    return {
        mWindowPosition.x + mWindowSize.w - 1,
        mWindowPosition.y + mWindowSize.h - 1
    };
}

// public
bool MicrosoftInnerWindow::setSize(const WindowSize& size) {
    return setSize(size.w, size.h);
}

// public
bool MicrosoftInnerWindow::setSize(int width, int height) {
    // OnWindowPosChanged will be called immediately after SetWindowPos
    WindowSize originalWindowSize = mWindowSize;
    mWindowSize = { width, height };

    if (SetWindowPos(mWinHandle, HWND_TOPMOST, 0, 0, width, height, SWP_NOACTIVATE | SWP_NOMOVE)) {
        return true;
    }

    // Rollback the window size if SetWindowPos fails
    mWindowSize = originalWindowSize;
    return false;
}

// public
WindowSize MicrosoftInnerWindow::getSize() const {
    return mWindowSize;
}

// public
bool MicrosoftInnerWindow::requestRedraw() {
    return InvalidateRect(mWinHandle, nullptr, false);
}

// public
bool MicrosoftInnerWindow::isLayered() const {
    return mIsLayered;
}

// public
std::shared_ptr<Canvas> MicrosoftInnerWindow::createCanvas() const {
    WindowRect windowRect = {
        .left = getTopLeft().x,
        .top = getTopLeft().y,
        .right = getBottomRight().x,
        .bottom = getBottomRight().y
    };
    return std::make_shared<Canvas>(mWinHandle, windowRect);
}

// private
void MicrosoftInnerWindow::registerClass(WNDPROC eventHandler) {
    if (!isClassRegistered()) {
        WNDCLASSEX wndClassEx = generateWinClassEx(eventHandler);
        RegisterClassEx(&wndClassEx);
    }
}

// private
bool MicrosoftInnerWindow::isClassRegistered() const {
    WNDCLASSEX wndClassEx = {};
    return GetClassInfoEx(mhInstance, mClassName.c_str(), &wndClassEx);
}

// private
WNDCLASSEX MicrosoftInnerWindow::generateWinClassEx(WNDPROC eventHandler) const {
    return WNDCLASSEX{
        .cbSize = sizeof(WNDCLASSEX),
        .style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        .lpfnWndProc = eventHandler,
        .hInstance = mhInstance,
        .hCursor = LoadCursor(nullptr, IDC_ARROW),
        .hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
        .lpszClassName = mClassName.c_str()
    };
}
