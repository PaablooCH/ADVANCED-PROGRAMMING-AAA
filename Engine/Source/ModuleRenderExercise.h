#pragma once
#include "Module.h"
#include "Model.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();
	
	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	inline Model* GetModel() {
		return model;
	}

private:
	Model* model;
	
};

