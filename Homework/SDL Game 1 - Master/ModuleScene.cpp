#include "ModuleScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include <vector>


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
	iterations = 0;

	flag.reserve(3);
	SDL_Rect sectionFlag;
	sectionFlag.x = 848;
	sectionFlag.y = 216;
	sectionFlag.w = 40;
	sectionFlag.h = 32;
	flag.push_back(sectionFlag);
	sectionFlag.x = 848;
	sectionFlag.y = 264;
	sectionFlag.w = 40;
	sectionFlag.h = 32;
	flag.push_back(sectionFlag);
	sectionFlag.x = 848;
	sectionFlag.y = 312;
	sectionFlag.w = 40;
	sectionFlag.h = 32;
	flag.push_back(sectionFlag);

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
	
	sectionFloor.x = 8 + movement;
	sectionFloor.y = 392;
	sectionFloor.w = SCREEN_WIDTH;
	sectionFloor.h = 72;

	App->renderer->Blit(scene, 0, 176, &sectionFloor);

	if (iterations < 33) 
	{
		App->renderer->Blit(scene, 560 - movement, 15, &flag[0]);
	}
	else if (iterations < 66)
	{
		App->renderer->Blit(scene, 560 - movement, 15, &flag[1]);
	}
	else 
	{
		App->renderer->Blit(scene, 560 - movement, 15, &flag[2]);
	}

	sumIteration();

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	return false;
}

void ModuleScene::move(int move)
{
	int aux = movement + move;
	if (aux > 0 && aux < 128) {
		movement = aux;
	}
}

void ModuleScene::sumIteration()
{
	iterations++;
	if (iterations >= 100) {
		iterations = 0;
	}
}
