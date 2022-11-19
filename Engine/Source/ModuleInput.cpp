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
                    App->camera->SetFOV(-5);
                }
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT && keyboard[SDL_SCANCODE_LALT]) {
                    App->camera->SetFOV(5);
                }
                break;
            case SDL_MOUSEMOTION:
                if (sdlEvent.motion.state == SDL_BUTTON_LMASK) { //Mouse Left button
                    
                }
                if (sdlEvent.motion.state == SDL_BUTTON_MMASK) { //Mouse Middle button
                    if (sdlEvent.motion.xrel < 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->MoveRight(10.f);
                        }
                        else {
                            App->camera->MoveRight(5.f);
                        }
                    }
                    if (sdlEvent.motion.xrel > 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->MoveLeft(10.f);
                        }
                        else {
                            App->camera->MoveLeft(5.f);
                        }
                    }
                    if (sdlEvent.motion.yrel > 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->GoDown(10.f);
                        }
                        else {
                            App->camera->GoDown(5.f);
                        }
                    }
                    if (sdlEvent.motion.yrel < 0) {
                        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                            App->camera->GoUp(10.f);
                        }
                        else {
                            App->camera->GoUp(5.f);
                        }
                    }
                }
                if (sdlEvent.motion.state == SDL_BUTTON_RMASK) { //Mouse Right button
                    if (sdlEvent.motion.xrel > 0) {
                        App->camera->RotationYClockwise(float(sdlEvent.motion.xrel));
                    }
                    else if (sdlEvent.motion.xrel < 0) {
                        App->camera->RotationYCounterclockwise(float(-sdlEvent.motion.xrel));
                    }
                    if (sdlEvent.motion.yrel > 0) {
                        App->camera->RotationXCounterclockwise(float(sdlEvent.motion.yrel));
                    }
                    else if (sdlEvent.motion.yrel < 0) {
                        App->camera->RotationXClockwise(float(-sdlEvent.motion.yrel));
                    }
                }
                break;
            case SDL_MOUSEWHEEL:
                if (sdlEvent.wheel.y > 0) // scroll up
                {
                    if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                        App->camera->MoveForward(20.f);
                    }
                    else {
                        App->camera->MoveForward(10.f);
                    }
                }
                else if (sdlEvent.wheel.y < 0) // scroll down
                {
                    if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
                        App->camera->MoveBackward(20.f);
                    }
                    else {
                        App->camera->MoveBackward(10.f);
                    }
                }
                break;
        }
    }

    if (keyboard[SDL_SCANCODE_ESCAPE]) {
        return UPDATE_STOP;
    }
    if (keyboard[SDL_SCANCODE_W]) { //MoveForward
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveForward(10.f);
        }
        else {
            App->camera->MoveForward(5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_S]) { //MoveBackward
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveBackward(10.f);
        }
        else {
            App->camera->MoveBackward(5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_A]) { //MoveLeft
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveLeft(10.f);
        }
        else {
            App->camera->MoveLeft(5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_D]) { //MoveRight
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->MoveRight(10.f);
        }
        else {
            App->camera->MoveRight(5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_Q]) { //GoUp
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->GoUp(10.f);
        }
        else {
            App->camera->GoUp(5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_E]) { // GoDown
        if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT]) {
            App->camera->GoDown(10.f);
        }
        else {
            App->camera->GoDown(5.f);
        }
    }
    if (keyboard[SDL_SCANCODE_UP]) {
        App->camera->RotationXClockwise(20.f);
    }
    if (keyboard[SDL_SCANCODE_DOWN]) {
        App->camera->RotationXCounterclockwise(20.f);
    }
    if (keyboard[SDL_SCANCODE_LEFT]) {
        App->camera->RotationYCounterclockwise(20.f);
    }
    if (keyboard[SDL_SCANCODE_RIGHT]) {
        App->camera->RotationYClockwise(20.f);
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
