#include "PanelModel.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"
#include "imgui.h"

PanelModel::PanelModel(const char* title) : Panel(title)
{
}

bool PanelModel::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(300, 480), ImGuiCond_Always);
    if (!ImGui::Begin(title, &open))
    {
        ImGui::End();
        return false;
    }

    ImGui::Text("Model Name:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", App->exercise->GetModel()->GetName());
    
    ImGui::End();
	return true;
}
