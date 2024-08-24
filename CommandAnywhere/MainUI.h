#pragma once
#include "microsoft_windows/MicrosoftWindow.h"
#include <chrono>
#include <string>

class MainUI
    : private IEvtListener
    , private IDrawer {

public:
    class IEventListener {
    public:
        virtual ~IEventListener() = default;
        virtual void onIconDoubleClicked() = 0;
    };

    MainUI(HINSTANCE hInstance, const std::wstring& className);

    void setListener(IEventListener& listener);

    void setIconSmall();

    void setIconLarge();

    void setChecked();

    void setUnchecked();

private:
    std::wstring getCheckedIconPath(int _0_or_1_);

    std::wstring getUncheckedIconPath();

    // IEvtListener's interface
    virtual void onMouse_LeftButton_DoubleClicked(const CursorLocation& cursorLocation) override; 

    // IEvtListener's interface
    virtual void onMouse_RightButton_Clicked(const CursorLocation& cursorLocation) override;

    // IEvtListener's interface
    virtual void onMouse_Hover(const CursorLocation& cursorLocation) override;

    // IDrawer's interface
    void draw(Canvas& canvas) override;


    MicrosoftWindow mMsWindow;

    IEventListener* mListener = nullptr;

    bool mIsChecked = true;

    int mCurCheckedIcon_0_or_1_ = 0;

    std::chrono::steady_clock::time_point last_icon_changed_time;
};


