#pragma once
#include "Common.h"
#include "WindowsEnvironmentVariableUtil.h"

class WindowsPathUtil {
public:
    WindowsPathUtil() = delete;

    // C:\Users\<user>\Downloads
    static DirPath userDownload() {
        return WindowsEnvironmentVariableUtil::currentUser() + LR"(\Downloads)";
    }
};

