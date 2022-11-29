#pragma once
#include "Module.h"
#include "GL/glew.h"
#include <string>

struct InfoTexture
{
	GLuint id;
	std::string path;
};

class ModuleTexture : public Module
{
public:
	void LoadTexture(const char* nameTexture, InfoTexture& info);
};

