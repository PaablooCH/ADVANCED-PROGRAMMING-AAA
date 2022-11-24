#pragma once
#include "Module.h"
#include "MathGeoLib/Geometry/Frustum.h"

class ModuleCamera :
    public Module
{
public:
	ModuleCamera();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void SetFOV(const float&& deg);
	void MoveFrontBack(const float&& multiplier);
	void MoveLeftRight(const float&& multiplier);
	void GoUpDown(const float&& multiplier);
	void RotationY(const float&& multiplier);
	void RotationX(const float&& multiplier);
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
	int speed;

	float4x4 proj;
	float4x4 view;
};

