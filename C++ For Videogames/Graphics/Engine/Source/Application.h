#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleRenderExercise;
//class ModuleEditor; //EDITOR
class ModuleDebugDraw;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* exercise = nullptr;
	//ModuleEditor* editor = nullptr; //EDITOR
	ModuleDebugDraw* debugdraw = nullptr;
	ModuleCamera* camera = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
