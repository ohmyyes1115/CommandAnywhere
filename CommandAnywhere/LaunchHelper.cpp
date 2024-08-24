#include "LaunchHelper.h"
#include <Windows.h>

using std::wstring;

// public static
static bool Execute(const wstring& exe, const wstring& args = L"", const wstring& dir = L"") {
    // Return value is greater than 32 if successful
    return (int)ShellExecute(NULL, NULL, (L'\"' + exe + L'\"').c_str(), args.c_str(), dir.c_str(), SW_SHOWDEFAULT) > 32;
}

// public static
void LaunchHelper::launchExplorer(const DirPath& dirPath) {
    wchar_t expandedDirPath[MAX_PATH];
    ExpandEnvironmentStrings(dirPath.c_str(), expandedDirPath, MAX_PATH);
    Execute(L"explorer", expandedDirPath);
}

// public static
void LaunchHelper::launchChrome() {
    Execute(L"chrome", L"\"https://www.google.com\"");
}

// public static
void LaunchHelper::launchGoogleMaps() {
    Execute(L"chrome", L"\"https://www.google.com/maps\"");
}

// public static
void LaunchHelper::launchGMail() {
    Execute(L"chrome", L"\"https://mail.google.com\"");
}

// public static
void LaunchHelper::launchCommandLine() {
    Execute(L"cmd");
}
