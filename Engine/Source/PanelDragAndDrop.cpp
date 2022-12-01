#include "PanelDragAndDrop.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "imgui.h"

PanelDragAndDrop::PanelDragAndDrop(const char* title) : Panel(title)
{
}

bool PanelDragAndDrop::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(300, 480), ImGuiCond_Always);
    if (!ImGui::Begin(title, &open))
    {
        ImGui::End();
        return false;
    }
    
    ImGui::End();
	return true;
}
