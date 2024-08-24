#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <functional>

class KeyboardHook {
public:
    using TypedCommand = std::string;

    class IListener {
    public:
        virtual ~IListener() = default;
        virtual void onCommandTyped(const TypedCommand& typedCommand) = 0;
    };

    KeyboardHook(HINSTANCE hInstance);

    ~KeyboardHook();

    static KeyboardHook& GetInstance(HINSTANCE hInstance = nullptr);

    static void onCommandTyped(const TypedCommand& typedCommand);

    bool AddListener(const IListener& listener);

    bool RemoveListener(const IListener& listener);

private:
    void NotifyCommandTyped(const TypedCommand& typedCommand);

    HINSTANCE mhInstance = nullptr;
    HHOOK mKbHook = nullptr;
    std::vector<IListener*> mListeners;
};

