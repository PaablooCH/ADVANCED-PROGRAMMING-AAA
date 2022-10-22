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
	iterations = 0;
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

	if (iterations < 33) {
		sectionFlag.x = 848;
		sectionFlag.y = 216;
		sectionFlag.w = 40;
		sectionFlag.h = 32;
	}
	else if (iterations < 66)
	{
		sectionFlag.x = 848;
		sectionFlag.y = 264;
		sectionFlag.w = 40;
		sectionFlag.h = 32;
	}
	else {
		sectionFlag.x = 848;
		sectionFlag.y = 312;
		sectionFlag.w = 40;
		sectionFlag.h = 32;
	}
	App->renderer->Blit(scene, 560 - movement, 15, &sectionFlag);

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
