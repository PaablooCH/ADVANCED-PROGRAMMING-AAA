#include "PanelConfig.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "imgui.h"
#include <vector>

PanelConfig::PanelConfig(const char* title) : Panel(title)
{
}

bool PanelConfig::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_Always);
    if (!ImGui::Begin(title, &open))
    {
        ImGui::End();
        return false;
    }

    if (ImGui::CollapsingHeader("Application"))
    {
        std::vector<float> fpsLogs = App->editor->GetFps();
        std::vector<float> miliLogs = App->editor->GetMili();
        char title[25];
        sprintf_s(title, 25, "Framerate %.1f", fpsLogs[fpsLogs.size() - 1]);
        ImGui::PlotHistogram("##framerate", &fpsLogs[0], fpsLogs.size(), 0, title, 0.0f, 200.0f, ImVec2(310.0f, 100.0f));
        sprintf_s(title, 25, "Milliseconds %.1f", miliLogs[miliLogs.size() - 1]);
        ImGui::PlotHistogram("##milliseconds", &miliLogs[0], miliLogs.size(), 0, title, 0.0f, 40.0f, ImVec2(310.0f, 100.0f));
    }
    if (ImGui::CollapsingHeader("Window"))
    {
        static bool winFullscreen = false;
        static bool winResizable = true;
        static bool winBorderless = false;
        static bool winFullscreenDsktp = false; //TODO implementar

        static float brightness = App->window->GetBrightness();

        if (ImGui::SliderFloat("Brightness", &brightness, 0, 1)) {
            App->window->SetBrightness(brightness);
        }

        static int widht = App->window->width;
        if (ImGui::SliderInt("Widht", &widht, 0, App->window->maxWidht)) {
            App->window->SetWidht(widht);
        }

        static int height = App->window->height;
        if (ImGui::SliderInt("Height", &height, 0, App->window->maxHeight)) {
            App->window->SetHeight(height);
        }


        if (ImGui::Checkbox("FULLSCREEN   |  ", &winFullscreen))
        {
            App->window->SetFullScreen(winFullscreen);

        }
        ImGui::SameLine();
        if (ImGui::Checkbox("RESIZABLE", &winResizable))
        {
            App->window->SetResizable(winResizable);
        }

        if (ImGui::Checkbox("BORDERLESS   |  ", &winBorderless))
        {
            App->window->SetBorderless(winBorderless);
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("FULLSCREEN DSKTP", &winFullscreenDsktp))
        {
            //TODO Implementar
        }
    }
    if (ImGui::CollapsingHeader("Hardware")) {
        SDL_version sdl_ver;
        SDL_VERSION(&sdl_ver);

        ImGui::Text("SDL version:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u.%u.%u", sdl_ver.major, sdl_ver.minor, sdl_ver.patch);
        ImGui::Separator();
        //-------------------------------
        ImGui::Text("CPUs:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u (Cache: %ukb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
        ImGui::Text("System RAM:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%uGb", SDL_GetSystemRAM());
        ImGui::Text("Caps:");
        ImGui::SameLine();
        std::vector<const char*> caps;
        if (SDL_Has3DNow()) {
            caps.emplace_back("3DNow");
        }
        if (SDL_HasAltiVec()) {
            caps.emplace_back("AltiVec");
        }
        if (SDL_HasAVX()) {
            caps.emplace_back("AVX");
        }
        if (SDL_HasAVX2()) {
            caps.emplace_back("AVX2");
        }
        if (SDL_HasMMX()) {
            caps.emplace_back("MMX");
        }
        if (SDL_HasRDTSC()) {
            caps.emplace_back("RDTSC");
        }
        if (SDL_HasSSE()) {
            caps.emplace_back("SSE");
        }
        if (SDL_HasSSE2()) {
            caps.emplace_back("SSE2");
        }
        if (SDL_HasSSE3()) {
            caps.emplace_back("SSE3");
        }
        if (SDL_HasSSE41()) {
            caps.emplace_back("SSE41");
        }
        if (SDL_HasSSE42()) {
            caps.emplace_back("SSE42");
        }
        for (int i = 0; i < caps.size(); i++) {
            if (i % 4 == 0 && i != 0) {
                ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", caps[i]);
            }
            else {
                ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", caps[i]);
                ImGui::SameLine();
            }
        }
        ImGui::Separator();
        //-------------------------------
        SDL_GetCurrentVideoDriver();
        ImGui::Text("GPU:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", SDL_GetCurrentVideoDriver()); //TODO falta la gpu
    }

    ImGui::End();
	return true;
}
