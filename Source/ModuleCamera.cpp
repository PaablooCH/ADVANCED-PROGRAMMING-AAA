#include "ModuleCamera.h"
#include "ModuleEditor.h"
#include "ModuleTimer.h"
#include "ModuleRender.h"
#include "Model.h"
#include "Application.h"
#include "MathGeoLib/Math/float3x3.h"
#include "MathGeoLib/Math/Quat.h"

ModuleCamera::ModuleCamera()
{
    frustum = new Frustum();
    rotateOption = false;
    speed = 10.f;
    farPlane = 100.0f;
    nearPlane = 0.1f;
}

bool ModuleCamera::Init()
{
    frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum->SetFrame(float3(0, 2, 8), -float3::unitZ, float3::unitY);
    frustum->SetViewPlaneDistances(nearPlane, farPlane);
    frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT));
    return true;
}

update_status ModuleCamera::PreUpdate()
{
    return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
    view = frustum->ViewMatrix();
    proj = frustum->ProjectionMatrix();

    return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    delete frustum;
    return true;
}

void ModuleCamera::SetFOV(const float&& fov)
{
    float recalculateFov = frustum->HorizontalFov() + fov;
    if (recalculateFov > 3) {
        recalculateFov = 3;
    }
    else if (recalculateFov < 1) {
        recalculateFov = 1;
    }
    frustum->SetHorizontalFovAndAspectRatio(recalculateFov, frustum->AspectRatio());
}

void ModuleCamera::MoveFrontBack(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Front() * speed * multiplier * App->timer->GetDeltaTime());
}

void ModuleCamera::MoveLeftRight(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->WorldRight() * speed * multiplier * App->timer->GetDeltaTime());
}

void ModuleCamera::GoUpDown(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * speed * multiplier * App->timer->GetDeltaTime());
}

void ModuleCamera::RotationCamera(const float&& multiplierX, const float&& multiplierY)
{
    Quat rotationX = Quat(float3::unitY, multiplierX * speed * App->timer->GetDeltaTime() * DEGTORAD);
    Quat rotationY = Quat(frustum->WorldMatrix().WorldX(), multiplierY * speed * App->timer->GetDeltaTime() * DEGTORAD);

    float3 up = rotationY.Transform(frustum->Up().Normalized());
    up = rotationX.Transform(up);

    float3 front = rotationY.Transform(frustum->Front().Normalized());
    front = rotationX.Transform(front);

    frustum->SetFront(front);
    frustum->SetUp(up);
}

void ModuleCamera::OrbitObject(const float&& multiplierX, const float&& multiplierY)
{
    float3 centerObject = App->renderer->GetModel()->GetCenter();
    // Get orbit point (object transform)
    float3 distance = frustum->Pos() - centerObject;

    // Rotate it
    Quat rotationX = Quat(frustum->Up(), multiplierX * speed * App->timer->GetDeltaTime() * DEGTORAD);
    Quat rotationY = Quat(frustum->WorldRight(), multiplierY * speed * App->timer->GetDeltaTime() * DEGTORAD);

    // If we look at the object from the bottom or top dont rotate the object
    float cosAngle = Dot(frustum->Front(), float3::unitY);
    if (cosAngle > 0.99f) {
        rotationY = Quat(frustum->WorldRight(), -0.5 * DEGTORAD);
    }
    else if (cosAngle < -0.99f) {
        rotationY = Quat(frustum->WorldRight(), 0.5 * DEGTORAD);
    }

    distance = rotationX.Transform(distance);
    distance = rotationY.Transform(distance);

    // Set camera to where the rotated vector points from its starting position
    frustum->SetPos(distance + centerObject);

    // Look At the object
    LookAt(centerObject);
}

void ModuleCamera::PosCameraViewObject(Model* model)
{
    float3 center = model->GetCenter();
    float3 minPoints = model->GetMinPoints();
    float3 maxPoints = model->GetMaxPoints();

    float3 pos;
    pos.z = center.z + minPoints.z - 1;
    pos.y = center.y + maxPoints.y + 1;
    pos.x = center.x + maxPoints.x + 1;
    frustum->SetPos(pos);
    LookAt(center);
}

void ModuleCamera::LookObject()
{
    LookAt(App->renderer->GetModel()->GetCenter());
}

void ModuleCamera::SetAspectRatio(const float& w, const float& h)
{
    frustum->SetHorizontalFovAndAspectRatio(frustum->HorizontalFov(), w / h);
}

void ModuleCamera::SetPlaneDistances(const float& n, const float& f)
{
    SetNearPlane(n);
    SetFarPlane(f);
    frustum->SetViewPlaneDistances(nearPlane, farPlane);
}

void ModuleCamera::Orientation(const vec& up)
{
    frustum->SetUp(up);
}

void ModuleCamera::LookAt(const float3& lookAt)
{
    float3 direction = lookAt - frustum->Pos();
    // localForward, targetDirection, localUp, worldUp
    float3x3 lookDir = float3x3::LookAt(frustum->Front(), direction.Normalized(), frustum->Up(), float3::unitY);
    frustum->SetFront(lookDir.MulDir(frustum->Front()).Normalized());
    frustum->SetUp(lookDir.MulDir(frustum->Up()).Normalized());
}