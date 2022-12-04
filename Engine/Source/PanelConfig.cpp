#include "PanelConfig.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"
#include "imgui.h"
#include <vector>

PanelConfig::PanelConfig(const char* title) : Panel(title)
{
}

bool PanelConfig::Draw()
{
    if (!open) {
        return false;
    }
    ImGui::SetNextWindowSize(ImVec2(420, 400), ImGuiCond_Always);
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
        bool fullscreen = false;
        bool resizable = true;
        bool borderless = false;
        bool fullscreenDsktp = false; //TODO implementar

        float brightness = App->window->GetBrightness();

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


        if (ImGui::Checkbox("FULLSCREEN   |  ", &fullscreen))
        {
            App->window->SetFullScreen(fullscreen);

        }
        ImGui::SameLine();
        if (ImGui::Checkbox("RESIZABLE", &resizable))
        {
            App->window->SetResizable(resizable);
        }

        if (ImGui::Checkbox("BORDERLESS   |  ", &borderless))
        {
            App->window->SetBorderless(borderless);
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("FULLSCREEN DSKTP", &fullscreenDsktp))
        {
            //TODO Implementar
        }
    }
    if (ImGui::CollapsingHeader("Render"))
    {
        float background[4] = { App->renderer->backgroundRGBA[0], App->renderer->backgroundRGBA[1], App->renderer->backgroundRGBA[2], App->renderer->backgroundRGBA[3] };
        ImGui::TextUnformatted("Color of the");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(background[0], background[1], background[2], 1.0f), "background");
        ImGui::SameLine();
        ImGui::TextUnformatted(":");

        ImGui::SetNextItemWidth(195);
        if (ImGui::ColorPicker3("##Background color1", (float*)&background, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs))
        {
            App->renderer->backgroundRGBA[0] = background[0];
            App->renderer->backgroundRGBA[1] = background[1];
            App->renderer->backgroundRGBA[2] = background[2];
            App->renderer->backgroundRGBA[3] = background[3];
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(195);
        if (ImGui::ColorPicker3("##Background color2", (float*)&background, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs))
        {
            App->renderer->backgroundRGBA[0] = background[0];
            App->renderer->backgroundRGBA[1] = background[1];
            App->renderer->backgroundRGBA[2] = background[2];
            App->renderer->backgroundRGBA[3] = background[3];
        }
        ImGui::SetNextItemWidth(390);
        if (ImGui::ColorEdit4("##Background input 1", (float*)&background, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float)) {
            App->renderer->backgroundRGBA[0] = background[0];
            App->renderer->backgroundRGBA[1] = background[1];
            App->renderer->backgroundRGBA[2] = background[2];
            App->renderer->backgroundRGBA[3] = background[3];
        }
        ImGui::SetNextItemWidth(390);
        if (ImGui::ColorEdit4("##Background input 2", (float*)&background, ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float)) {
            App->renderer->backgroundRGBA[0] = background[0];
            App->renderer->backgroundRGBA[1] = background[1];
            App->renderer->backgroundRGBA[2] = background[2];
            App->renderer->backgroundRGBA[3] = background[3];
        }

        ImGui::Separator();

        float3 color = App->renderer->GetColorGrid();
        float grid[3] = { color.x, color.y, color.z };
        ImGui::TextUnformatted("Color of the");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(color.x, color.y, color.z, 1.0f), "grid");
        ImGui::SameLine();
        ImGui::TextUnformatted(":");

        ImGui::SetNextItemWidth(195);
        if (ImGui::ColorPicker3("##Grid color1", (float*)&grid, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs))
        {
            App->renderer->SetColorGrid(float3(grid[0], grid[1], grid[2]));
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(195);
        if (ImGui::ColorPicker3("##Grid color2", (float*)&grid, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs))
        {
            App->renderer->SetColorGrid(float3(grid[0], grid[1], grid[2]));
        }
        ImGui::SetNextItemWidth(390);
        if (ImGui::ColorEdit4("##Grid input 1", (float*)&grid, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float)) {
            App->renderer->SetColorGrid(float3(grid[0], grid[1], grid[2]));
        }
        ImGui::SetNextItemWidth(390);
        if (ImGui::ColorEdit4("##grid input 2", (float*)&grid, ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float)) {
            App->renderer->SetColorGrid(float3(grid[0], grid[1], grid[2]));
        }

    }
    if (ImGui::CollapsingHeader("Camera")) { //TODO acabar
        float angley = 0.f;
        float speed = App->camera->GetSpeed();
        bool rotationOption = App->camera->GetRotationOption();

        if (ImGui::SliderFloat("Rotate X", &angley, -1, 1)) {
            App->camera->RotationCamera(0.f, std::move(angley));
        }
        if (ImGui::SliderFloat("Rotate Y", &angley, -1, 1)) {
            App->camera->RotationCamera(0.f, std::move(angley));
        }
        if (ImGui::SliderFloat("Speed", &speed, 0.1f, 20.f)) {
            App->camera->SetSpeed(speed);
        }
        if (ImGui::Checkbox("Rotation Option", &rotationOption)) {
            App->camera->SetRotateOption(rotationOption);
        }
        if (ImGui::SmallButton("Focus Model")) { App->camera->LookObject(); }
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
