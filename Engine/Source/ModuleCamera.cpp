#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleEditor.h"
#include "ModuleTimer.h"
#include "ModuleRenderExercise.h"
#include "Application.h"
#include "MathGeoLib/Math/float3x3.h"
#include "MathGeoLib/Math/Quat.h"

ModuleCamera::ModuleCamera()
{
    frustum = new Frustum();
    rotateOption = false;
    speed = 10.f;
}

bool ModuleCamera::Init()
{
    frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum->SetFrame(float3(0, 2, 8), -float3::unitZ, float3::unitY);
    frustum->SetViewPlaneDistances(0.1f, 100.0f);
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

    App->debugdraw->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);

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

void ModuleCamera::SetFOV(const float&& deg)
{
    frustum->SetHorizontalFovAndAspectRatio(frustum->HorizontalFov() + DEGTORAD * deg, frustum->AspectRatio());
}

void ModuleCamera::MoveFrontBack(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Front() * speed * multiplier * App->timer->deltaTime);
}

void ModuleCamera::MoveLeftRight(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->WorldRight() * speed * multiplier * App->timer->deltaTime);
}

void ModuleCamera::GoUpDown(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * speed * multiplier * App->timer->deltaTime);
}

void ModuleCamera::RotationCamera(const float&& multiplierX, const float&& multiplierY)
{
    Quat rotationX = Quat(frustum->Up(), multiplierX * speed * App->timer->deltaTime * DEGTORAD);
    Quat rotationY = Quat::RotateX(multiplierY * speed * App->timer->deltaTime * DEGTORAD);

    float3 up = rotationX.Transform(frustum->Up());
    up = rotationY.Transform(up);

    float3 front = rotationX.Transform(frustum->Front());
    front = rotationY.Transform(front);

    frustum->SetFront(front);
    frustum->SetUp(up);
}

void ModuleCamera::OrbitObject(const float&& multiplierX, const float&& multiplierY)
{
    float3 centerObject = App->exercise->GetModel()->GetCenter();
    // Get orbit point (object transform)
    float3 distance = frustum->Pos() - centerObject;

    // Rotate it
    Quat rotationX = Quat(frustum->Up(), multiplierX * speed * App->timer->deltaTime * DEGTORAD);
    Quat rotationY = Quat(frustum->WorldRight(), multiplierY * speed * App->timer->deltaTime * DEGTORAD);

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

void ModuleCamera::LookObject()
{
    float3 center = App->exercise->GetModel()->GetCenter();
    float3 minPoints = App->exercise->GetModel()->GetMinPoints();
    float3 maxPoints = App->exercise->GetModel()->GetMaxPoints();

    float3 pos = center;
    pos.z = pos.z + 2.5f*minPoints.z;
    pos.y = pos.y + 2*maxPoints.y;
    pos.x = pos.x + 2*maxPoints.x;
    frustum->SetPos(pos);
    LookAt(center);
}

void ModuleCamera::SetAspectRatio(const float& w, const float& h)
{
    App->editor->logs.emplace_back("Aspect Ratio changed");
    frustum->SetHorizontalFovAndAspectRatio(frustum->HorizontalFov(), w / h);
}

void ModuleCamera::SetPlaneDistances(const float& near, const float& far)
{
    frustum->SetViewPlaneDistances(0.1f, 100.0f);
}

void ModuleCamera::Position(const vec& pos)
{
    frustum->SetPos(pos); //TODO inservible
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