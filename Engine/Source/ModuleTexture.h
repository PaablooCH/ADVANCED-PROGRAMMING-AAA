#pragma once
#include "Module.h"
#include "DirectXTex/DirectXTex.h"
#include "GL/glew.h"
#include <string>

using namespace DirectX;

struct Info
{
	GLint id;
	std::string path;
};

class ModuleTexture : public Module
{
public:
	void LoadTexture(const char* nameTexture, Info& info);
};

