#pragma once
#include <string>
#include "Common.h"

class LaunchHelper
{
public:
    static void launchExplorer(const DirPath& dirPath);
    
    static void launchChrome();

    static void launchGoogleMaps();

    static void launchGMail();

    static void launchCommandLine();
};

