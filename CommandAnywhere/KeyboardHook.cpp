#include "KeyboardHook.h"
#include <sstream>
#include <ranges>

using std::string;
using std::ostringstream;
using std::ranges::find_if;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

// TODO:
// 1. Use RAII to manage the hook
// 2. Dependency injection: pass the trigger key to KeyboardHook
// 3. Use a state machine to manage the command typing
// 4. Split the command detection into 2 stages: trigger key detection and command typing

// public
KeyboardHook::KeyboardHook(HINSTANCE hInstance)
    : mhInstance(hInstance) {
}

// public
KeyboardHook::~KeyboardHook() {
    UnhookWindowsHookEx(mKbHook);
}

// public static
KeyboardHook& KeyboardHook::GetInstance(HINSTANCE hInstance) {
    static KeyboardHook instance(hInstance);
    return instance;
}

// public static
void KeyboardHook::onCommandTyped(const TypedCommand& typedCommand) {
    KeyboardHook::GetInstance().NotifyCommandTyped(typedCommand);
}

// public
bool KeyboardHook::AddListener(const IListener& listener) {
    if (mListeners.empty()) {
        mKbHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, mhInstance, 0);
    }

    mListeners.push_back(const_cast<IListener*>(&listener));
    return true;
}

// public
bool KeyboardHook::RemoveListener(const IListener& listener) {
    std::erase_if(mListeners, [&](const IListener* eachListener) { return &listener == eachListener; });

    if (mListeners.empty()) {
        UnhookWindowsHookEx(mKbHook);
    }

    return true;
}

// private
void KeyboardHook::NotifyCommandTyped(const TypedCommand& typedCommand) {
    for (auto listener : mListeners) {
        listener->onCommandTyped(typedCommand);
    }
}

// [NOTE]
//     1. If the key processing is too long (> 200ms ?), system force deliver this key to next candidate
static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    static bool sIsCommandTyping = false;
    static ostringstream oss;
    bool isKeyConsumed = false;

    if (nCode >= 0) {
        LPKBDLLHOOKSTRUCT pKbs = (LPKBDLLHOOKSTRUCT)lParam;
        int vkCode = pKbs->vkCode;

        // trigger key
        // win + z
        int triggerKey_sys = VK_LWIN;
        char triggerKey_char = toupper('Z');

        // Win is NOT a system-key, so 'triggerKey_chart' will be a WM_KEYDOWN
        bool isCmdTypingTriggerKey = (vkCode == triggerKey_char) && (wParam == WM_KEYDOWN) && GetKeyState(triggerKey_sys) & 0x8000;

        // ALT is a system-key, so 'triggerKey_chart' will be a WM_SYSKEYDOWN
        //bool isCmdTypingTriggerKey = (vkCode == triggerKey_char) && (wParam == WM_SYSKEYDOWN) && GetKeyState(triggerKey_sys) & 0x8000;

        if (isCmdTypingTriggerKey) {
            sIsCommandTyping = true;
            // Use 'Win + Z' as example:
            //      1. System always receives keys in the later order (later than application)
            //      2. In order to let system support single 'Win' press
            //         We can't consume 'Win' KEY_DOWN or KEY_UP
            //      3. If we consumed the 'Z', system will be unware of the 'Z',
            //         after the 'Win' KEY_UP passed to system, system will trigger a 'Win' pressed function
            //isKeyConsumed = true;

            oss = ostringstream();
        }
        else if (sIsCommandTyping) {
            // Enter
            if ((vkCode == VK_RETURN) && (wParam == WM_KEYDOWN)) {
                sIsCommandTyping = false;
                isKeyConsumed = true;

                string curCommand = oss.str();
                oss = ostringstream();

                KeyboardHook::onCommandTyped(curCommand);
            }
            // ESC
            else if ((vkCode == VK_ESCAPE) && (wParam == WM_KEYDOWN)) {
                sIsCommandTyping = false;
                isKeyConsumed = true;

                oss = ostringstream();
            }
            // Character
            else if (wParam == WM_KEYDOWN) {
                oss << static_cast<char>(vkCode);
                isKeyConsumed = true;
            }
        }

        if (isKeyConsumed) {
            constexpr int KEY_CONSUMED = 1;
            return KEY_CONSUMED;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
