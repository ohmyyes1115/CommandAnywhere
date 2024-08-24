#pragma once
#include <unordered_map>
#include <functional>
#include <string>

class CustomCommands {
public:
    using Runnable = std::function<void()>;

    void registerAsyncCommand(Runnable runnable, const std::initializer_list<std::string>& commands);

    bool exeCommand(const std::string& command);

private:
    std::unordered_map<std::string, Runnable> mAsyncCommands;
};

