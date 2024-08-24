#pragma once
#include "MicrosoftWindowsUtil.h"
#include <Windows.h>

class Canvas {
public:
    Canvas(HWND _hwnd, WindowRect& _windowRect);

    ~Canvas();

    // layered style
    void apply();

    HDC hdc = nullptr;

    WindowRect windowRect;

private:
    HWND hwnd = nullptr;

    HDC hdcScreen = nullptr;

    PAINTSTRUCT ps;

    HBITMAP hBmp = nullptr;
};


