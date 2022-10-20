#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
struct SDL_Rect;

class ModuleScene : public Module
{
public:

	ModuleScene();
	~ModuleScene();

	bool Init();
	void Start() override;
	update_status Update() override;
	bool CleanUp();

	int movement;

private:
	SDL_Texture* scene;
	SDL_Rect section;
};

