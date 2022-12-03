#pragma once
#include "Module.h"
#include "MathGeoLib/Geometry/Frustum.h"

class Model;

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
	void RotationCamera(const float&& multiplierX, const float&& multiplierY);
	void OrbitObject(const float&& multiplierX, const float&& multiplierY);
	void PosCameraViewObject(Model* model);
	void LookObject();
	void SetAspectRatio(const float& w, const float& h);
	void SetPlaneDistances(const float& near, const float& far);
	void Position(const vec& pos);
	void Orientation(const vec& up);
	void LookAt(const float3& lookAt);
	inline const float4x4& ProjectionMatrix() {
		return proj;
	}
	inline const float4x4& GetViewMatrix() {
		return view;
	}

	bool rotateOption; //True -> arround an object, false -> her axis

private:
	Frustum* frustum;
	float speed;

	float4x4 proj;
	float4x4 view;
};

