#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
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
	LOG_ENGINE("Init SDL input event system");
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

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        //ImGui_ImplSDL2_ProcessEvent(&sdlEvent);  //EDITOR
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
        }
    }

    keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_ESCAPE]) {
        return UPDATE_STOP;
    }

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG_ENGINE("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
