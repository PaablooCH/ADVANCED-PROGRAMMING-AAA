#include "ModuleRenderExercise.h"
#include "Application.h"
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
	model = new Model("Bakerhouse.fbx");
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
