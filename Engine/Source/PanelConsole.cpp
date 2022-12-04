#include "PanelConsole.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "imgui.h"

PanelConsole::PanelConsole(const char* title) : Panel(title)
{
}

bool PanelConsole::Draw()
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

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Close Console"))
            open = false;
        ImGui::EndPopup();
    }

    if (ImGui::SmallButton("Clear")) { App->editor->ClearLog(); }
    ImGui::SameLine();
    bool copyToClipboard = ImGui::SmallButton("Copy");

    ImGui::Separator();

    const float footerHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footerHeightToReserve), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) App->editor->ClearLog();
            ImGui::EndPopup();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
        if (copyToClipboard)
            ImGui::LogToClipboard();
        for (int i = 0; i < App->editor->logs.size(); i++)
        {
            const char* item = App->editor->logs[i];

            ImVec4 color;
            bool hasColor = false;
            if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); hasColor = true; }
            else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); hasColor = true; }
            if (hasColor)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            if (hasColor)
                ImGui::PopStyleColor();
        }
        if (copyToClipboard)
            ImGui::LogFinish();

        if (scrollToBottom || (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();

    focus = ImGui::IsWindowFocused();

    ImGui::End();
	return true;
}
