#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
#include "MathGeoLib/Math/float3.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class Model;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;
	void WindowResized(unsigned width, unsigned height);
	void DropFile(const char* pathFile);

	inline Model* GetModel() {
		return model;
	}
	inline const unsigned& GetProgram() {
		return program;
	}
	inline float3& GetColorGrid() {
		return colorGrid;
	}
	inline void SetColorGrid(float3 color) {
		colorGrid = color;
	}

	float backgroundRGBA[4] = { 0.3f, 0.3f, 0.3f, 1.f };

public:
	void* context;
	unsigned program;
	Model* model;

	float3 colorGrid;
};
