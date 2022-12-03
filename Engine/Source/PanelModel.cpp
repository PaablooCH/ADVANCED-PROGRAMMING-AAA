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

    Model* model = App->exercise->GetModel();

    ImGui::Text("Model Name:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", model->GetName().c_str());

    ImGui::Text("Center Point:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "x:%f", model->GetCenter().x);
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "              y:%f", model->GetCenter().y);
    ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "              z:%f", model->GetCenter().z);

    if (ImGui::CollapsingHeader("Textures"))
    {
        for (InfoTexture material : model->GetMaterials()) {
            ImGui::Text("-  Id:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u", material.id);
            ImGui::SameLine();
            ImGui::Text("Name:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", material.path.c_str());
            ImGui::Text("  ");
            ImGui::SameLine();
            ImGui::Image((void*)(intptr_t)material.id, ImVec2(100, 100));
        }
    }

    if (ImGui::CollapsingHeader("Meshes"))
    {
        for (Mesh* mesh : model->GetMeshes()) {
            ImGui::Text("-  Num Vertices:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u", mesh->GetNumVertices());
            ImGui::Text("   Num Indices:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u", mesh->GetNumIndices());
            ImGui::Text("   Material Index:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u", mesh->GetMaterialIndex());
        }
    }
    
    ImGui::End();
	return true;
}
