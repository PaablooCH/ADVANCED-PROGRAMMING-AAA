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

	void SetFOV(const float&& deg);
	void MoveForward(const float&& multiplier);
	void MoveBackward(const float&& multiplier);
	void MoveLeft(const float&& multiplier);
	void MoveRight(const float&& multiplier);
	void GoUp(const float&& multiplier);
	void GoDown(const float&& multiplier);
	void RotationYClockwise(const float&& multiplier);
	void RotationXClockwise(const float&& multiplier);
	void RotationYCounterclockwise(const float&& multiplier);
	void RotationXCounterclockwise(const float&& multiplier);
	void SetAspectRatio(const float& w, const float& h);
	void SetPlaneDistances(const float& near, const float& far);
	void Position(const vec& pos);
	void Orientation(const vec& up);
	void LookAt(const float& x, const float& y, const float& z);
	inline float4x4 ProjectionMatrix() {
		return proj;
	}
	inline float4x4 GetViewMatrix() {
		return view;
	}

private:
	Frustum* frustum;

	float4x4 proj;
	float4x4 view;
};

