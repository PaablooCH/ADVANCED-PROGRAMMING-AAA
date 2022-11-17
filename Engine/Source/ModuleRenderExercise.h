#pragma once
#include "Module.h"
#include "DirectXTex/DirectXTex.h"
using namespace DirectX;

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();
	
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
private:
	int program;
	unsigned vbo, tbo, ebo, vao;
	
};

