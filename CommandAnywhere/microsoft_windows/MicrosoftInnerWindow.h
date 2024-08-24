#pragma once
#include "microsoft_windows/Canvas.h"
#include "Common.h"
#include "MicrosoftWindowsUtil.h"
#include <Windows.h>

struct MsWindowEventHandler {
    WNDPROC wndProc;
    LPVOID lpParam;
};

class MicrosoftInnerWindow {
public:
    MicrosoftInnerWindow(
        int dwStyle,
        int dwExStyle,
        HINSTANCE hInstance,
        const std::wstring& className,
        const MsWindowEventHandler& eventHandler);

    virtual ~MicrosoftInnerWindow();

    bool show();

    bool hide();

    bool setPosition(const WindowPosition& topLeft);

    bool setPosition(int left, int top);

    WindowPosition getTopLeft() const;

    WindowPosition getBottomRight() const;

    bool setSize(const WindowSize& size);

    bool setSize(int width, int height);

    WindowSize getSize() const;

    bool requestRedraw();

    bool isLayered() const;

    std::shared_ptr<Canvas> createCanvas() const;

private:
    void registerClass(WNDPROC eventHandler);

    bool isClassRegistered() const;

    WNDCLASSEX generateWinClassEx(WNDPROC eventHandler) const;

    HINSTANCE mhInstance = nullptr;

    const std::wstring mClassName;

    bool mIsLayered = false;

    HWND mWinHandle = nullptr;

    WindowPosition mWindowPosition;

    WindowSize mWindowSize;
};

