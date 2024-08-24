#include "MicrosoftWindow.h"
#include "MsInnerWindowFactory.h"
#include "ParamUtil.h"

using std::wstring;

MicrosoftWindow::MicrosoftWindow(HINSTANCE hInstance, const wstring& className, IEvtListener* evtListener, IDrawer* drawer)
    : mhInstance(hInstance)
    , mClassName(className)
    , mEvtListener(evtListener)
    , mDrawer(drawer)
    , mInnerWindow(MsInnerWindowFactory::CreateDefaultWindow(hInstance, className, MsWindowEventHandler{ HandleEvent, this })) {}

// public
MicrosoftWindow::~MicrosoftWindow() {
    //SetThis(mWndHandle, nullptr);
}

// public
void MicrosoftWindow::show() {
    if (!isVisible() && mInnerWindow.show()) {
        mIsVisible = true;
        doRedraw();
    }
}

// public
void MicrosoftWindow::hide() {
    if (isVisible() && mInnerWindow.hide()) {
        mIsVisible = false;
    }
}

// public
void MicrosoftWindow::setPosition(int left, int top) {
    mInnerWindow.setPosition(left, top);
}

// public
void MicrosoftWindow::setSize(int width, int height) {
    mInnerWindow.setSize(width, height);
}

// public
void MicrosoftWindow::requestRedraw() {
    if (mInnerWindow.isLayered()) {
        doRedraw();
    }
    else {
        mInnerWindow.requestRedraw();
    }
}

// public
bool MicrosoftWindow::isVisible() const {
    return mIsVisible;
}

// private
void MicrosoftWindow::doRedraw() {
    if (mDrawer) {
        if (std::shared_ptr<Canvas> canvas = mInnerWindow.createCanvas()) {
            mDrawer->draw(*canvas);
            canvas->apply();
        }
    }
}

// WndProc event handlers++

// private
void MicrosoftWindow::onPaint() {
    doRedraw();
}

// private
void MicrosoftWindow::onMouse_LeftButton_Clicked(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_LeftButton_Clicked(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_LeftButton_Down(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_LeftButton_Down(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_LeftButton_UP(const MouseState& mouseState) {
    if (mIsDragging) {
        onMouse_LeftButtonDrag_Finished();
        mIsDragging = false;
        mIsMouseLButtonDown = false;
    }

    onMouse_LeftButton_Clicked(mouseState);
    ReleaseCapture();
}

// private
void MicrosoftWindow::onMouse_LeftButton_DoubleClicked(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_LeftButton_DoubleClicked(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_LeftButtonDrag_Begun(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_LeftButtonDrag_Begun(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_LeftButtonDrag_Ing(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_LeftButtonDrag_Ing(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_LeftButtonDrag_Finished() {
    if (mEvtListener) {
        mEvtListener->onMouse_LeftButtonDrag_Finished();
    }
}

// private
void MicrosoftWindow::onMouse_RightButton_Clicked(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_RightButton_Clicked(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_RightButton_DoubleClicked(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_RightButton_DoubleClicked(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_RightButton_Down(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_RightButton_Down(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_RightButton_UP(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_RightButton_UP(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_RightButtonDrag_Begun(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_RightButtonDrag_Begun(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_RightButtonDrag_Ing(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_RightButtonDrag_Ing(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_RightButtonDrag_Finished() {
    if (mEvtListener) {
        mEvtListener->onMouse_RightButtonDrag_Finished();
    }
}

// private
void MicrosoftWindow::onMouse_Wheel(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    if (mEvtListener) {
        mEvtListener->onMouse_Wheel(hwnd, wParam, lParam);
    }
}

// private
void MicrosoftWindow::onMouse_Hover(const MouseState& mouseState) {
    if (mEvtListener) {
        mEvtListener->onMouse_Hover(mouseState.cursorLocation);
    }
}

// private
void MicrosoftWindow::onMouse_Moving(HWND hwnd, const MouseState& mouseState) {
    if (!mouseState.leftButtonPressed) {
        onMouse_Hover(mouseState);
    }
    else {
        if (!mIsMouseLButtonDown) {
            SetCapture(hwnd);
            onMouse_LeftButtonDrag_Begun(mouseState);
            mIsMouseLButtonDown = true;
            mIsDragging = true;
        }
    }

    if (mIsMouseLButtonDown) {
        onMouse_LeftButtonDrag_Ing(mouseState);
    }
}

// private
void MicrosoftWindow::onWindowPos_Changed() {
    requestRedraw();
}

// WndProc event handlers--

// private static
LRESULT MicrosoftWindow::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CREATE) {
        SetParentPointer(hWnd, (reinterpret_cast<CREATESTRUCT*>(lParam))->lpCreateParams);
    }

    MicrosoftWindow* microsoftWindow = GetParentPointer(hWnd);
    if (!microsoftWindow) {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    switch (uMsg) {
    case WM_PAINT:
        microsoftWindow->doRedraw();
        break;

    // mouse > L-button
    case WM_LBUTTONDBLCLK:
        microsoftWindow->onMouse_LeftButton_DoubleClicked(ParamUtil::GetMouseState(wParam, lParam));
        break;

    // mouse > L-button
    case WM_LBUTTONDOWN:
        microsoftWindow->onMouse_LeftButton_Down(ParamUtil::GetMouseState(wParam, lParam));
        break;

    // mouse > L-button
    case WM_LBUTTONUP:
        microsoftWindow->onMouse_LeftButton_UP(ParamUtil::GetMouseState(wParam, lParam));
        break;

    // mouse > R-button
    case WM_RBUTTONDBLCLK:
        microsoftWindow->onMouse_RightButton_DoubleClicked(ParamUtil::GetMouseState(wParam, lParam));
        break;

    // mouse > R-button
    case WM_RBUTTONDOWN:
        microsoftWindow->onMouse_RightButton_Down(ParamUtil::GetMouseState(wParam, lParam));
        break;

    // mouse > R-button
    case WM_RBUTTONUP:
        microsoftWindow->onMouse_RightButton_UP(ParamUtil::GetMouseState(wParam, lParam));
        break;

    // mouse > move
    case WM_MOUSEMOVE:
        microsoftWindow->onMouse_Moving(hWnd, ParamUtil::GetMouseState(wParam, lParam));
        break;

    // mouse > wheel
    case WM_MOUSEWHEEL:
        microsoftWindow->onMouse_Wheel(hWnd, wParam, lParam);
        break;

    // window position > changed
    case WM_WINDOWPOSCHANGED:
        microsoftWindow->onWindowPos_Changed();
        break;

    case WM_KEYDOWN:
        break;

    case WM_KEYUP:
        break;

    // TODO: Support DPI changed

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

// private static
void MicrosoftWindow::SetParentPointer(HWND hwnd, void* parent) {
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(parent));
}

// private static
MicrosoftWindow* MicrosoftWindow::GetParentPointer(HWND hwnd) {
    return reinterpret_cast<MicrosoftWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}
