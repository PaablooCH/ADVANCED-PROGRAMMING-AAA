#include "PanelModel.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Model.h"
#include "Mesh.h"
#include "ModuleEditor.h"
#include "imgui.h"

PanelModel::PanelModel(const char* title) : Panel(title)
{
}

bool PanelModel::Draw()
{
    if (!open) {
        focus = false;
        return false;
    }
    ImGui::SetNextWindowSize(ImVec2(300, 480), ImGuiCond_Once);
    if (!ImGui::Begin(title, &open))
    {
        focus = false;
        ImGui::End();
        return false;
    }

    Model* model = App->renderer->GetModel();

    ImGui::Text("Model Name:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", model->GetName().c_str());

    float4x4 matrix = model->GetMatrix();
    ImGui::Text("Matrix transform:");
    ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.2f, 1.0f), "%f, %f, %f, %f", matrix.Row(0).x, matrix.Row(0).y, matrix.Row(0).z, matrix.Row(0).z);
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%f, %f, %f, %f", matrix.Row(1).x, matrix.Row(1).y, matrix.Row(1).z, matrix.Row(1).z);
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%f, %f, %f, %f", matrix.Row(2).x, matrix.Row(2).y, matrix.Row(2).z, matrix.Row(2).z);
    ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.5f, 1.0f), "%f, %f, %f, %f", matrix.Row(3).x, matrix.Row(3).y, matrix.Row(3).z, matrix.Row(3).z);

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
    
    focus = ImGui::IsWindowFocused();

    ImGui::End();
	return true;
}
