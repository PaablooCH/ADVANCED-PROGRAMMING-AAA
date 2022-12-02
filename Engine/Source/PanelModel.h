#pragma once
#include "Panel.h"
class PanelModel :
    public Panel
{
public:
    PanelModel(const char* title);
    bool Draw();
};

