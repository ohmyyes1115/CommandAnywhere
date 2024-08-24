#include "LaunchHelper.h"
#include <Windows.h>
#include <tlhelp32.h>  // PROCESSENTRY32

using std::wstring;

// TODO: Encapsulate win32 functions
HWND findMainWindow(unsigned long process_id) {
    HWND hwnd = GetTopWindow(0);
    while (hwnd) {
        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid == process_id) {
            return hwnd;
        }
        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
    }
    return 0;
}

static HINSTANCE simpleShellExecute(const wstring& exe, const wstring& args = L"", const wstring& dir = L"") {
    // Return value is greater than 32 if successful
    return ShellExecute(nullptr, nullptr, (L'\"' + exe + L'\"').c_str(), args.c_str(), dir.c_str(), SW_SHOW);
}

// public static
static bool execute(const wstring& exe, const wstring& args = L"", const wstring& dir = L"") {
    return reinterpret_cast<int>(simpleShellExecute(exe, args, dir)) > 32;
}

// public static
static bool execute_BringToTop(const wstring& exe, const wstring& args = L"", const wstring& dir = L"") {
    const wstring targetExe = exe + L".exe";
    HINSTANCE hInstance = simpleShellExecute(exe, args, dir);

    if (reinterpret_cast<int>(hInstance) > 32) {
        PROCESSENTRY32 entry = {};
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (Process32First(snapshot, &entry)) {
            while (Process32Next(snapshot, &entry)) {
                if (_wcsicmp(entry.szExeFile, targetExe.c_str()) == 0) {
                    HWND hwnd = findMainWindow(entry.th32ProcessID);
                    if (hwnd) {
                        SetForegroundWindow(hwnd);
                    }
                    break;
                }
            }
        }

        CloseHandle(snapshot);
        return true;
    }
    else {
        return false;
    }
}

// public static
void LaunchHelper::launchExplorer(const DirPath& dirPath) {
    wchar_t expandedDirPath[MAX_PATH];
    ExpandEnvironmentStrings(dirPath.c_str(), expandedDirPath, MAX_PATH);
    execute(L"explorer", expandedDirPath);
}

// public static
void LaunchHelper::launchChrome() {
    execute_BringToTop(L"chrome", L"\"https://www.google.com\"");
}

// public static
void LaunchHelper::launchGoogleMaps() {
    execute_BringToTop(L"chrome", L"\"https://www.google.com/maps\"");
}

// public static
void LaunchHelper::launchGMail() {
    execute_BringToTop(L"chrome", L"\"https://mail.google.com\"");
}

// public static
void LaunchHelper::launchCommandLine() {
    execute(L"cmd");
}
