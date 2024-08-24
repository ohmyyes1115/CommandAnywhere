#include "MainUI.h"
#include "Common.h"

#include <atlimage.h>

using std::wstring;
using namespace std::chrono;

static const DirPath AssetPath = Common::GetExeDirPath() + L"\\asset";

// public
MainUI::MainUI(HINSTANCE hInstance, const wstring& className)
    : mMsWindow(hInstance, className, this, this) {

    mMsWindow.setPosition(1350, 0);
    setIconLarge();
    mMsWindow.show();
}

// public
void MainUI::setListener(IEventListener& listener) {
    mListener = &listener;
}

// public
void MainUI::setIconSmall() {
    mMsWindow.setSize(30, 30);
}

// public
void MainUI::setIconLarge() {
    mMsWindow.setSize(60, 60);
}

// public
void MainUI::setChecked() {
    auto now = steady_clock::now();
    long long duration_last_icon_changed = duration_cast<milliseconds>(now - last_icon_changed_time).count();

    // Don't change check-icon too frequent.
    //   If the case is:
    //       check-1  -(fast)->  check-2  -(fast)-> check-1   
    //   it's not easy to find out that icon has changed.
    if (duration_last_icon_changed > 300) {
        last_icon_changed_time = now;
        mCurCheckedIcon_0_or_1_ = (mCurCheckedIcon_0_or_1_ + 1) % 2;
    }

    mIsChecked = true;

    mMsWindow.requestRedraw();
}

// public
void MainUI::setUnchecked() {
    if (mIsChecked) {
        mIsChecked = false;
        mMsWindow.requestRedraw();
    }
}

// private
std::wstring MainUI::getCheckedIconPath(int _0_or_1_) {
    if (_0_or_1_ == 0) {
        return AssetPath + L"\\check1.jpg";
    }
    else {
        return AssetPath + L"\\check2.jpg";
    }
}

// private
std::wstring MainUI::getUncheckedIconPath() {
    return AssetPath + L"\\x.jpg";
}

// private
// IEvtListener's interface
void MainUI::onMouse_LeftButton_DoubleClicked(const CursorLocation& cursorLocation) {
    if (mListener) {
        mListener->onIconDoubleClicked();
    }
}

// private
// IEvtListener's interface
void MainUI::onMouse_RightButton_Clicked(const CursorLocation& cursorLocation) {
    // TODO: Display context menu
}

// private
// IEvtListener's interface
void MainUI::onMouse_Hover(const CursorLocation& cursorLocation) {
}

// private
// IDrawer's interface
void MainUI::draw(Canvas& canvas) {
    std::wstring icon_filePath;

    if (mIsChecked) {
        icon_filePath = getCheckedIconPath(mCurCheckedIcon_0_or_1_);
    }
    else {
        icon_filePath = getUncheckedIconPath();
    }

    CImage srcImg;
    srcImg.Load(icon_filePath.c_str());

    int dstWidth = canvas.windowRect.getWidth();
    int dstHeight = canvas.windowRect.getHeight();

    // Draw image to memory DC
    srcImg.Draw(canvas.hdc, 0, 0, dstWidth, dstHeight, 0, 0, srcImg.GetWidth(), srcImg.GetHeight());
}
