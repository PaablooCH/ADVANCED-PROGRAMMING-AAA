#pragma once
#include "Panel.h"
class PanelConsole :
    public Panel
{
public:
    PanelConsole(const char* title);
    bool Draw() override;
    bool CleanUp() {
        delete this;
        return true;
    }

private:
    bool autoScroll;
    bool scrollToBottom;
};

