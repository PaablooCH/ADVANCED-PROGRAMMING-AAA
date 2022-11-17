#pragma once
#include "Module.h"
#include "DirectXTex/DirectXTex.h"
using namespace DirectX;

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();
	
	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;
private:
	int program;
	unsigned vbo, tbo, ebo, vao;
	
};

