#pragma once
#include "MicrosoftInnerWindow.h"
#include <Windows.h>

class MsInnerWindowFactory {
public:
    static MicrosoftInnerWindow CreateDefaultWindow(HINSTANCE hInstance, const std::wstring& className, const MsWindowEventHandler& eventHandler) {
        return CreateLayerWindow(hInstance, className, eventHandler);
    } 

private:
    class DefaultConfig {
    public:
        static int GetDwStyle() {
            return WS_POPUP;
        }

        static int GetDwExStyle() {
            return WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_TOPMOST;
        }
    };

    class LayeredConfig {
    public:
        static int GetDwStyle() {
            return DefaultConfig::GetDwStyle();
        }

        static int GetDwExStyle() {
            return DefaultConfig::GetDwExStyle() | WS_EX_LAYERED;
        }
    };

    static MicrosoftInnerWindow CreateBasicWindow(HINSTANCE hInstance, const std::wstring& className, const MsWindowEventHandler& eventHandler) {
        return MicrosoftInnerWindow(
            DefaultConfig::GetDwStyle(), DefaultConfig::GetDwExStyle(), hInstance, className, eventHandler);
    }

    static MicrosoftInnerWindow CreateLayerWindow(HINSTANCE hInstance, const std::wstring& className, const MsWindowEventHandler& eventHandler) {
        return MicrosoftInnerWindow(
            LayeredConfig::GetDwStyle(), LayeredConfig::GetDwExStyle(), hInstance, className, eventHandler);
    }
};

