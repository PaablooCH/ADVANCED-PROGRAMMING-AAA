#pragma once
#include "Panel.h"
class PanelAbout :
    public Panel
{
public:
    PanelAbout(const char* title);
    bool Draw() override;
};

