#pragma once
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:

	ModuleScene();
	~ModuleScene();

	bool Init();
	void Start() override;
	update_status Update() override;
	bool CleanUp();

private:
	SDL_Texture* scene;
};

