#include "Controller.h"
#include "WindowsPathUtil.h"
#include "LaunchHelper.h"

// public
Controller::Controller(MainUI& mainUI, KeyboardHook& keyboardHook)
    : mMainUI(mainUI)
    , mKeyboardHook(keyboardHook)
    , mFunctionActive(true) {

    mMainUI.setListener(*this);

    // 'Win + Z' to start command typing

    mCustomCommands.registerAsyncCommand([&] {
        LaunchHelper::launchExplorer(LR"(D:\)"); }, { "proj" });

    mCustomCommands.registerAsyncCommand([&] {
        // C:\Users\<user>\Downloads
        LaunchHelper::launchExplorer(WindowsPathUtil::userDownload()); }, { "dl" });

    mCustomCommands.registerAsyncCommand([&] {
        LaunchHelper::launchCommandLine(); }, { "cmd" });

    mCustomCommands.registerAsyncCommand([&] {
        LaunchHelper::launchChrome(); }, { "google search", "gs" });

    mCustomCommands.registerAsyncCommand([&] {
        LaunchHelper::launchGoogleMaps(); }, { "google maps", "gmp" , "map" });

    mCustomCommands.registerAsyncCommand([&] {
        LaunchHelper::launchGMail(); }, { "gmail", "gml", "mail" });

    refreshByActiveState();
}

// public
Controller::~Controller()
{
    mFunctionActive = false;
    refreshByActiveState();
}

// private
void Controller::toggleFunctionality() {
    mFunctionActive = !mFunctionActive;
    refreshByActiveState();
}

// private
void Controller::refreshByActiveState() {
    if (mFunctionActive) {
        mMainUI.setChecked();
        mMainUI.setIconLarge();

        mKeyboardHook.AddListener(*this);
    }
    else {
        mMainUI.setUnchecked();
        mMainUI.setIconSmall();

        mKeyboardHook.RemoveListener(*this);
    }
}

// private
// implement MainWindow::IEventListener
void Controller::onIconDoubleClicked() {
    toggleFunctionality();
}

// private
// implement KeyboardHook::IEventListener
void Controller::onCommandTyped(const KeyboardHook::TypedCommand& typedCommand) {
    mCustomCommands.exeCommand(typedCommand);
}
