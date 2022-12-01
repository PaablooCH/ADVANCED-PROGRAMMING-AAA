#include "ModuleRenderExercise.h"
#include "Globals.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	return true;
}

bool ModuleRenderExercise::Start()
{
	model = new Model("Models/Bakerhouse.fbx");
	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	model->Draw();
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	delete model;
	return true;
}

void ModuleRenderExercise::DropFile(const char* pathFile)
{
	delete model;
	model = new Model(pathFile);
}
