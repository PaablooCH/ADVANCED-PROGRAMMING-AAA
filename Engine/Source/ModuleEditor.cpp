#include "ModuleEditor.h"
#include "Panel.h"
#include "PanelConsole.h"
#include "PanelConfig.h"
#include "PanelAbout.h"
#include "PanelModel.h"
#include "PanelLog.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTimer.h"
#include "GL/glew.h"
#include <string>

ModuleEditor::ModuleEditor()
{
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

    panels.push_back(console = new PanelConsole("Console"));
    panels.push_back(config = new PanelConfig("Configuration"));
    panels.push_back(about = new PanelAbout("About"));
    panels.push_back(model = new PanelModel("Model Information"));

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
    miliLogs.emplace_back(App->timer->GetMili());

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{

    if (!DrawMainMenu()) {
        return UPDATE_STOP;
    }

    for (std::list<Panel*>::iterator it = panels.begin(); it != panels.end(); ++it) {
        (*it)->Draw();
    }

    //ImGui::ShowDemoWindow(); //TODO eliminarlo al final
    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(App->window->window, App->renderer->context);

    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    for (std::list<Panel*>::iterator it = panels.begin(); it != panels.end(); ++it) {
        delete (*it);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();
	return true;
}

bool ModuleEditor::FocusPanels()
{
    for (std::list<Panel*>::iterator it = panels.begin(); it != panels.end(); ++it) {
        if ((*it)->GetFocus()) { return true; }
    }
    return false;
}

bool ModuleEditor::DrawMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit")) {
                return false;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("About", NULL, &about->GetOpen())) {
                about->SetOpen(true);
            }
            if (ImGui::MenuItem("Console Log", NULL, &console->GetOpen())) {
                console->SetOpen(true);
            }
            if (ImGui::MenuItem("Configuration", NULL, &config->GetOpen())) {
                config->SetOpen(true);
            }
            if (ImGui::MenuItem("Model", NULL, &model->GetOpen())) {
                model->SetOpen(true);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Github"))
        {
            if (ImGui::MenuItem("Main Page")) {
                ShellExecuteA(NULL, "open", "https://github.com/PaablooCH/ADVANCED-PROGRAMMING-AAA", NULL, NULL, SW_SHOWNORMAL);
            }
            if (ImGui::MenuItem("Documentation")) {
                ShellExecuteA(NULL, "open", "https://github.com/PaablooCH/ADVANCED-PROGRAMMING-AAA/wiki", NULL, NULL, SW_SHOWNORMAL);
            }
            if (ImGui::MenuItem("Download Latest")) {
                ShellExecuteA(NULL, "open", "https://github.com/PaablooCH/ADVANCED-PROGRAMMING-AAA/releases", NULL, NULL, SW_SHOWNORMAL);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    return true;
}