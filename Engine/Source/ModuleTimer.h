#pragma once
#include "Module.h"
class ModuleTimer :
    public Module
{
public:
	
	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	float deltaTime;
	float miliseconds;

private:
	long lastTime;
};

