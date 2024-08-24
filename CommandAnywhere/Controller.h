#pragma once
#include "MainUI.h"
#include "KeyboardHook.h"
#include "CustomCommands.h"

class Controller
    : private MainUI::IEventListener
    , private KeyboardHook::IListener {

public:
    Controller(MainUI& mainUI, KeyboardHook& keyboardHook);

    ~Controller();

private:
    void toggleFunctionality();

    void refreshByActiveState();

    // implement MainWindow::IEventListener
    virtual void onIconDoubleClicked() override;

    // implement KeyboardHook::IEventListener
    virtual void onCommandTyped(const KeyboardHook::TypedCommand& typedCommand) override;

    MainUI& mMainUI;
    KeyboardHook& mKeyboardHook;
    CustomCommands mCustomCommands;

    bool mFunctionActive;
};
