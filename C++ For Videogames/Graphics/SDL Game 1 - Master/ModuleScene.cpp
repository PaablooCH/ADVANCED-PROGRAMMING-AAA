#include "ModuleScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"


ModuleScene::ModuleScene()
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Init()
{
	scene = App->textures->Load("ken_stage.png");
	return true;
}

void ModuleScene::Start()
{
}

update_status ModuleScene::Update()
{
	SDL_Rect section;
	section.x = 0;
	section.y = 0;
	section.w = 500;
	section.h = 500;
	App->renderer->Blit(scene, 0, 0, &section);
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	return false;
}
