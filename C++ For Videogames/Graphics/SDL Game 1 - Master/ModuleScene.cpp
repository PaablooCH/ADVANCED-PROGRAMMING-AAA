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
	movement = 0;
	return true;
}

void ModuleScene::Start()
{
}

update_status ModuleScene::Update()
{
	section.x = 72 + movement;
	section.y = 210;
	section.w = SCREEN_WIDTH;
	section.h = 176;
	App->renderer->Blit(scene, 0, 0, &section);

	SDL_Rect sectionFloor;
	sectionFloor.x = 8 + movement;
	sectionFloor.y = 392;
	sectionFloor.w = SCREEN_WIDTH;
	sectionFloor.h = 72;
	App->renderer->Blit(scene, 0, 176, &sectionFloor);

	SDL_Rect sectionFloor;
	sectionFloor.x = 632 + movement;
	sectionFloor.y = 392;
	sectionFloor.w = 42;
	sectionFloor.h = 72;
	App->renderer->Blit(scene, 0, 176, &sectionFloor);

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	return false;
}
