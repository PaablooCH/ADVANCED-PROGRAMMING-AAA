#include "PanelAbout.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "imgui.h"

PanelAbout::PanelAbout(const char* title) : Panel(title)
{
}

bool PanelAbout::Draw()
{
    if (!open) {
        focus = false;
        return false;
    }
    ImGui::SetNextWindowSize(ImVec2(450, 400), ImGuiCond_Once);
    if (!ImGui::Begin(title, &open))
    {
        focus = false;
        ImGui::End();
        return false;
    }

    ImGui::Text("Engine Name:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Deus Ex Machina");

    ImGui::Text("Description:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "With <3 by Pablo Cebollada Hernandez.");

    ImGui::Text("Author:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Pablo Cebollada Hernandez");

    ImGui::Text("Libraries:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "glew 2.1.0,");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "SDL2,");
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "DirectXTex October 2022 version,");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "MathGeoLib,");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ImGui,");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Assimp &");
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "DirectX.");

    ImGui::Text("License:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "MIT License.");

    focus = ImGui::IsWindowFocused();

    ImGui::End();
    return false;
}
