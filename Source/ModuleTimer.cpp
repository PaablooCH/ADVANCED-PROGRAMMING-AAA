#include "ModuleTimer.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "SDL.h"

bool ModuleTimer::Init()
{
    App->editor->logs.emplace_back("Start counting");
    lastTime = SDL_GetTicks();
    return true;
}

bool ModuleTimer::Start()
{
    return true;
}

update_status ModuleTimer::PreUpdate()
{
    long currentTime = SDL_GetTicks();

    miliseconds = float(currentTime - lastTime);

    deltaTime = miliseconds / 1000.0f;
    if (deltaTime < HIGH_LIMIT) {
        deltaTime = HIGH_LIMIT;
    }
    else if (deltaTime > LOW_LIMIT) {
        deltaTime = LOW_LIMIT;
    }

    lastTime = currentTime;
    return UPDATE_CONTINUE;
}

update_status ModuleTimer::Update()
{
    return UPDATE_CONTINUE;
}

update_status ModuleTimer::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleTimer::CleanUp()
{
    return true;
}
