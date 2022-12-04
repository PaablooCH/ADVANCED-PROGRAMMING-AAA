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

	void SetFOV(const float&& fov);
	void MoveFrontBack(const float&& multiplier);
	void MoveLeftRight(const float&& multiplier);
	void GoUpDown(const float&& multiplier);
	void RotationCamera(const float&& multiplierX, const float&& multiplierY);
	void OrbitObject(const float&& multiplierX, const float&& multiplierY);
	void PosCameraViewObject(Model* model);
	void LookObject();
	void SetAspectRatio(const float& w, const float& h);
	void SetPlaneDistances(const float& n, const float& f);
	void Orientation(const vec& up);
	void LookAt(const float3& lookAt);
	inline const float4x4& GetProjectionMatrix() {
		return proj;
	}
	inline const float4x4& GetViewMatrix() {
		return view;
	}
	inline float& GetSpeed() {
		return speed;
	}
	inline void SetSpeed(const float& s) {
		speed = s;
	}
	inline float& GetFarPlane() {
		return farPlane;
	}
	inline void SetFarPlane(const float& farP) {
		farPlane = farP;
	}
	inline float& GetNearPlane() {
		return nearPlane;
	}
	inline void SetNearPlane(const float& nearP) {
		nearPlane = nearP;
	}
	inline bool& GetRotationOption() {
		return rotateOption;
	}
	inline void SetRotateOption(const bool& option) {
		rotateOption = option;
	}

private:
	Frustum* frustum;
	float speed, nearPlane, farPlane;
	bool rotateOption; //True -> arround an object, false -> her axis

	float4x4 proj;
	float4x4 view;
};

