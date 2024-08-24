#pragma once
#include "Common.h"

class WindowsEnvironmentVariableUtil {
public:
    WindowsEnvironmentVariableUtil() = delete;

    static FilePath currentUser() {
        return ExpandEnvironmentVariable(L"%USERPROFILE%");
    };

private:
    static FilePath ExpandEnvironmentVariable(const DirPath& unExpandedDirPath) {
        wchar_t expandedEnvVar[MAX_PATH];
        ExpandEnvironmentStrings(unExpandedDirPath.c_str(), expandedEnvVar, MAX_PATH);
        return expandedEnvVar;
    };
};

