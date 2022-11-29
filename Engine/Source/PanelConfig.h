#pragma once
#include "Panel.h"
class PanelConfig :
    public Panel
{
public:
    PanelConfig(const char* title);
    bool Draw() override;
};

