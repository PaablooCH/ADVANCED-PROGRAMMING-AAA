#pragma once
#include "Module.h"
#include "MathGeoLib/Geometry/Frustum.h"

class ModuleCamera :
    public Module
{
public:
	ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void SetFOV(int deg);
	void SetAspectRatio(int w, int h);
	void SetPlaneDistances(); 
	void Position(); 
	void Orientation(); 
	void LookAt(int x, int y, int z);
	inline float4x4 ProjectionMatrix() {
		return frustum->ProjectionMatrix();
	}
	inline float4x4 GetViewMatrix() {
		return frustum->ViewMatrix();
	}

private:
	Frustum* frustum;
	float aspect; //TODO temp o long

	float4x4 proj;
	float4x4 view;
};

