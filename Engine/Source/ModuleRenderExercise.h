#pragma once
#include "Module.h"

class Model;

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

	void DropFile(const char* pathFile);

	inline Model* GetModel() {
		return model;
	}

private:
	Model* model;
	
};

