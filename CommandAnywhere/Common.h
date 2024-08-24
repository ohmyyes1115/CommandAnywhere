#pragma once
#include <Windows.h>
#include <filesystem>

using FilePath = std::wstring;
using DirPath = std::wstring;

struct Size { int w = 0; int h = 0; };

struct Point { int x = 0; int y = 0; };

struct Rect {
    int getWidth() const {
        return (right - left + 1);
    }

    int getHeight() const {
        return (bottom - top + 1);
    }

    int left = 0; int top = 0; int right = 0; int bottom = 0;
};

class Common {
public:
    Common() = delete;

    static FilePath GetExeFilePath() {
        wchar_t buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);
        return buffer;
    }

    static DirPath GetExeDirPath() {
        FilePath exePath = GetExeFilePath();
        return std::filesystem::path(exePath).parent_path().wstring();
    }
};
