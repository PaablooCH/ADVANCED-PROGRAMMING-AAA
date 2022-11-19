#include "ModuleEditor.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTimer.h"
#include "GL/glew.h"

ModuleEditor::ModuleEditor()
{
    clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
    //LOG_ENGINE("Create ImGui context")
    logs.emplace_back("Create ImGui context");
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    return true;
}

bool ModuleEditor::Start()
{
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    ++loops;

    if (loops >= maxSizeFPS) {
        fpsLogs.erase(fpsLogs.begin());
        miliLogs.erase(miliLogs.begin());
    }
    fpsLogs.emplace_back(ImGui::GetIO().Framerate);
    miliLogs.emplace_back(App->timer->miliseconds);

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
    bool openConsole = false;
    bool openConfig = false;
    bool openAbout = false;

    DrawLog("Console", openConsole);
    DrawConfig("Configuration", openConfig);
    ImGui::ShowDemoWindow();
    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(App->window->window, App->renderer->context);

    //SDL_GL_SwapWindow(App->window->window);

    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();
	return true;
}

void ModuleEditor::DrawLog(const char* title, bool& p_open)
{
    ImGui::SetNextWindowSize(ImVec2(300, 480), ImGuiCond_Always);
    if (!ImGui::Begin(title, &p_open))
    {
        ImGui::End();
        return;
    }

    // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
    // So e.g. IsItemHovered() will return true when hovering the title bar.
    // Here we create a context menu only available from the title bar.
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Close Console"))
            p_open = false;
        ImGui::EndPopup();
    }

    // TODO: display items starting from the bottom

    if (ImGui::SmallButton("Clear")) { ClearLog(); }
    ImGui::SameLine();
    bool copy_to_clipboard = ImGui::SmallButton("Copy");
    //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

    ImGui::Separator();

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &autoScroll);
        ImGui::EndPopup();
    }

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) ClearLog();
            ImGui::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets.
        // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
        // to only process visible items. The clipper will automatically measure the height of your first item and then
        // "seek" to display only items in the visible area.
        // To use the clipper we can replace your standard loop:
        //      for (int i = 0; i < Items.Size; i++)
        //   With:
        //      ImGuiListClipper clipper;
        //      clipper.Begin(Items.Size);
        //      while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // - That your items are evenly spaced (same height)
        // - That you have cheap random access to your elements (you can access them given their index,
        //   without processing all the ones before)
        // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
        // We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
        // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
        // to improve this example code!
        // If your items are of variable height:
        // - Split them into same height items would be simpler and facilitate random-seeking into your list.
        // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (int i = 0; i < logs.size(); i++)
        {
            const char* item = logs[i];
            
            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.)
            ImVec4 color;
            bool has_color = false;
            if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
            else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            if (has_color)
                ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (scrollToBottom || (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        scrollToBottom = false;

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    ImGui::End();
}

void ModuleEditor::DrawConfig(const char* title, bool& p_open)
{
    ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_Always);
    if (!ImGui::Begin(title, &p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("Stats"))
    {
        char title[25];
        sprintf_s(title, 25, "Framerate %.1f", fpsLogs[fpsLogs.size() - 1]);
        ImGui::PlotHistogram("##framerate", &fpsLogs[0], fpsLogs.size(), 0, title, 0.0f, 200.0f, ImVec2(310.0f, 100.0f));
        sprintf_s(title, 25, "Milliseconds %.1f", miliLogs[miliLogs.size() - 1]);
        ImGui::PlotHistogram("##milliseconds", &miliLogs[0], miliLogs.size(), 0, title, 0.0f, 40.0f, ImVec2(310.0f, 100.0f));
        ImGui::Separator();
    }

    ImGui::SetItemDefaultFocus();
    ImGui::End();
}
