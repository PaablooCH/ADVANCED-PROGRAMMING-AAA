#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"
#include "SDL.h"
#include "imgui_impl_sdl.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	//LOG_ENGINE("Init SDL input event system");
    App->editor->logs.emplace_back("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG_ENGINE("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
        ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;
    keyboard = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                }
                if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE) {
                    return UPDATE_STOP;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (sdlEvent.button.button == SDL_BUTTON_LEFT && keyboard[SDL_SCANCODE_LALT]) {
                    App->camera->SetRotateOption(!App->camera->GetRotationOption());
                    App->editor->logs.emplace_back("Rotation Option changed");
                }
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT && keyboard[SDL_SCANCODE_RALT]) {
                    App->camera->SetFOV(0.1f);
                }
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT && keyboard[SDL_SCANCODE_LALT]) {
                    App->camera->SetFOV(-0.1f);
                }
                break;
            case SDL_MOUSEMOTION:
                if (sdlEvent.motion.state == SDL_BUTTON_LMASK) { //Mouse Left button
                    
                }
                if (sdlEvent.motion.state == SDL_BUTTON_MMASK) { //Mouse Middle button
                    if (sdlEvent.motion.xrel < 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->MoveLeftRight(-2.f);
                        }
                        else {
                            App->camera->MoveLeftRight(-1.f);
                        }
                    }
                    if (sdlEvent.motion.xrel > 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->MoveLeftRight(2.f);
                        }
                        else {
                            App->camera->MoveLeftRight(1.f);
                        }
                    }
                    if (sdlEvent.motion.yrel > 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->GoUpDown(-2.f);
                        }
                        else {
                            App->camera->GoUpDown(-1.f);
                        }
                    }
                    if (sdlEvent.motion.yrel < 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->GoUpDown(2.f);
                        }
                        else {
                            App->camera->GoUpDown(1.f);
                        }
                    }
                }
                if (sdlEvent.motion.state == SDL_BUTTON_RMASK) { //Mouse Right button
                    if (!App->camera->GetRotationOption()) { //Rotate camera
                        App->camera->RotationCamera(float(-sdlEvent.motion.xrel), float(-sdlEvent.motion.yrel));
                    }
                    else { //Rotate arround object
                        App->camera->OrbitObject(float(-sdlEvent.motion.xrel), float(-sdlEvent.motion.yrel));
                    }
                }
                break;
            case SDL_MOUSEWHEEL:
                if (sdlEvent.wheel.y > 0) // scroll up
                {
                    if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                        App->camera->MoveFrontBack(10.f);
                    }
                    else {
                        App->camera->MoveFrontBack(5.f);
                    }
                }
                else if (sdlEvent.wheel.y < 0) // scroll down
                {
                    if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                        App->camera->MoveFrontBack(-10.f);
                    }
                    else {
                        App->camera->MoveFrontBack(-5.f);
                    }
                }
                break;

            case SDL_DROPFILE:
                App->editor->logs.emplace_back("File dropped");
                App->renderer->DropFile(sdlEvent.drop.file);
                break;
        }
    }

    if (keyboard[SDL_SCANCODE_ESCAPE]) {
        return UPDATE_STOP;
    }
    if (keyboard[SDL_SCANCODE_W]) { //MoveForward
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveFrontBack(2.f);
        }
        else {
            App->camera->MoveFrontBack(1.f);
        }
    }
    if (keyboard[SDL_SCANCODE_S]) { //MoveBackward
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveFrontBack(-2.f);
        }
        else {
            App->camera->MoveFrontBack(-1.f);
        }
    }
    if (keyboard[SDL_SCANCODE_A]) { //MoveLeft
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveLeftRight(-2.f);
        }
        else {
            App->camera->MoveLeftRight(-1.f);
        }
    }
    if (keyboard[SDL_SCANCODE_D]) { //MoveRight
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveLeftRight(2.f);
        }
        else {
            App->camera->MoveLeftRight(1.f);
        }
    }
    if (keyboard[SDL_SCANCODE_Q]) { //GoUp
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->GoUpDown(2.f);
        }
        else {
            App->camera->GoUpDown(1.f);
        }
    }
    if (keyboard[SDL_SCANCODE_E]) { // GoDown
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->GoUpDown(-2.f);
        }
        else {
            App->camera->GoUpDown(-1.f);
        }
    }
    if (keyboard[SDL_SCANCODE_F]) {
        App->camera->LookObject();
    }
    if (keyboard[SDL_SCANCODE_UP]) {
        if (!App->camera->GetRotationOption()) { //Rotate camera
            App->camera->RotationCamera(0.f, 5.f);
        }
        else { //Rotate arround object
            App->camera->OrbitObject(0.f, -5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_DOWN]) {
        if (!App->camera->GetRotationOption()) { //Rotate camera
            App->camera->RotationCamera(0.f, -5.f);
        }
        else { //Rotate arround object
            App->camera->OrbitObject(0.f, 5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_LEFT]) {
        if (!App->camera->GetRotationOption()) { //Rotate camera
            App->camera->RotationCamera(5.f, 0.f);
        }
        else { //Rotate arround object
            App->camera->OrbitObject(5.f, 0.f);
        }
    }
    if (keyboard[SDL_SCANCODE_RIGHT]) {
        if (!App->camera->GetRotationOption()) { //Rotate camera
            App->camera->RotationCamera(-5.f, 0.f);
        }
        else { //Rotate arround object
            App->camera->OrbitObject(-5.f, 0.f);
        }
    }

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	//LOG_ENGINE("Quitting SDL input event subsystem");
    App->editor->logs.emplace_back("Quitting SDL input event subsystem");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
