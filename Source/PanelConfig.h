#pragma once
#include "Panel.h"
#include <dxgi1_4.h>

class PanelConfig :
    public Panel
{
public:
    PanelConfig(const char* title);
    bool Draw() override;
private:
    IDXGIFactory2* pDXGIFactory = nullptr;
    IDXGIAdapter3* pDXGIAdapter = nullptr;
    DXGI_QUERY_VIDEO_MEMORY_INFO localVideoMemoryInfo;
};

