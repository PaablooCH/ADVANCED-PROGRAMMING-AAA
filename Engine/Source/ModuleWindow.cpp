#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG_ENGINE("Init SDL window & surface");
	App->editor->logs.emplace_back("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ENGINE("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		maxWidht = dm.w;
		maxHeight = dm.h;
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if (RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if (FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG_ENGINE("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	//LOG_ENGINE("Destroying SDL window and quitting all SDL systems");
	App->editor->logs.emplace_back("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetFullScreen(bool fullScreen)
{
	fullScreen ? SDL_SetWindowFullscreen(window, SDL_TRUE) : SDL_SetWindowFullscreen(window, SDL_FALSE);
}

void ModuleWindow::SetBorderless(bool borderless)
{
	borderless ? SDL_SetWindowBordered(window, SDL_FALSE) : SDL_SetWindowBordered(window, SDL_TRUE);
}

void ModuleWindow::SetResizable(bool resizable)
{
	resizable ? SDL_SetWindowResizable(window, SDL_TRUE) : SDL_SetWindowResizable(window, SDL_FALSE);
}

void ModuleWindow::SetBrightness(float brightness)
{
	SDL_SetWindowBrightness(window, brightness);
}

void ModuleWindow::SetWidht(int w)
{
	width = w;
	SDL_SetWindowSize(window, width, height);
}

void ModuleWindow::SetHeight(int h)
{
	height = h;
	SDL_SetWindowSize(window, width, height);
}

float ModuleWindow::GetBrightness()
{
	return SDL_GetWindowBrightness(window);
}
