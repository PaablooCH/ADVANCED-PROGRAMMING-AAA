#pragma once
#include "Module.h"
#include "DirectXTex/DirectXTex.h"
using namespace DirectX;

class ModuleTexture : public Module
{
public:
	bool Init();
	void LoadTexture(const wchar_t* nameTexture, TexMetadata* metadata, ScratchImage& image);
};

