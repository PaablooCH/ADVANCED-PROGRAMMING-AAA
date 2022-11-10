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

	void SetFOV(const int& deg);
	void SetAspectRatio(const float& w, const float& h);
	void SetPlaneDistances(const float& near, const float& far);
	void Position(const vec& pos);
	void Orientation(const vec& up);
	void LookAt(const float& x, const float& y, const float& z);
	inline float4x4 ProjectionMatrix() {
		return frustum->ProjectionMatrix();
	}
	inline float4x4 GetViewMatrix() {
		return frustum->ViewMatrix();
	}

private:
	Frustum* frustum;

	float4x4 proj;
	float4x4 view;
};

