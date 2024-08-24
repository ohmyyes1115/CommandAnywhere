#include "CustomCommands.h"
#include <algorithm>
#include <future>

using std::string;
using std::thread;
using std::initializer_list;
using std::ranges::transform;

// public
// TODO: Move async logic out of this class
void CustomCommands::registerAsyncCommand(Runnable runnable, const initializer_list<string>& commands) {
    // Register the command with all lowercase letters
    for (auto& command : commands) {
        string commandLowercase = command;
        transform(command, commandLowercase.begin(), std::tolower);

        mAsyncCommands[commandLowercase] = runnable;
    }
}

// public
bool CustomCommands::exeCommand(const string& command) {
    string commandLowercase = command;
    transform(command, commandLowercase.begin(), std::tolower);

    if (mAsyncCommands.contains(commandLowercase)) {
        thread(mAsyncCommands[commandLowercase]).detach();
        return true;
    }

    return false;
}