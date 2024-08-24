#include "Canvas.h"

// public
Canvas::Canvas(HWND _hwnd, WindowRect& _windowRect)
    : hwnd(_hwnd)
    , windowRect(_windowRect) {

    // TODO: Error handling
    hdcScreen = BeginPaint(hwnd, &ps);
    hdc = CreateCompatibleDC(hdcScreen);
    hBmp = CreateCompatibleBitmap(
        hdcScreen, windowRect.getWidth(), windowRect.getHeight());
    HBITMAP hBmpOld = (HBITMAP)SelectObject(hdc, hBmp);
}

// public
Canvas::~Canvas() {
    DeleteDC(hdc);
    DeleteObject(hBmp);
    EndPaint(hwnd, &ps);
}

// public
// layered style
void Canvas::apply() {
    // blending
    //SIZE bgSIZE = { rect.right, rect.bottom };
    POINT ptSRC = { 0,0 };
    //BLENDFUNCTION blend{ AC_SRC_OVER, 0, ALPHA_MAX, AC_SRC_ALPHA };
    BLENDFUNCTION blend{ AC_SRC_OVER, 0,       200,            0 };

    // size & position
    POINT ptPos = { windowRect.left, windowRect.top };
    SIZE sizeWnd = { windowRect.getWidth(), windowRect.getHeight() };
    POINT ptSrc = { 0, 0 };

    //Log_I(L"[YYY::%s] pos = (%d, %d)   size = (%d, %d)", TAG, ptPos.x, ptPos.y, sizeWnd.cx, sizeWnd.cy);
    //UpdateLayeredWindow(hwnd, NULL, NULL, &bgSIZE, hdc, &ptSRC, NULL, &blend, ULW_ALPHA);

    UpdateLayeredWindow(hwnd, hdcScreen, &ptPos, &sizeWnd, hdc, &ptSrc, 0, &blend, ULW_ALPHA);
}