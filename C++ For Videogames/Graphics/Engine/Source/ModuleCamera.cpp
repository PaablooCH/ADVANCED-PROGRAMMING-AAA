#include "ModuleCamera.h"
#include "GL/glew.h"
#include "ModuleDebugDraw.h"
#include "Application.h"
#include "MathGeoLib/Math/float3x3.h"
#include "MathGeoLib/Math/float4x4.h"

ModuleCamera::ModuleCamera()
{
}

bool ModuleCamera::Init()
{
    frustum = new Frustum();
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

void ModuleCamera::SetFOV(const int& deg)
{
    frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * deg, frustum->AspectRatio());
}

void ModuleCamera::MoveForward()
{
    frustum->SetPos(frustum->Pos() + frustum->Front() * 0.1f);
}

void ModuleCamera::MoveBackward()
{
    frustum->SetPos(frustum->Pos() + frustum->Front() * -0.1f);
}

void ModuleCamera::MoveLeft()
{
    frustum->SetPos(frustum->Pos() + frustum->WorldRight() * -0.1f);
}

void ModuleCamera::MoveRight()
{
    frustum->SetPos(frustum->Pos() + frustum->WorldRight() * 0.1f);
}

void ModuleCamera::GoUp()
{
    frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * .1f);
}

void ModuleCamera::GoDown()
{
    frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * -.1f);
}

void ModuleCamera::RotationYClockwise()
{
    float3x3 rotationMatrix = float3x3::RotateY(DEGTORAD * -1);
    vec oldFront = frustum->Front().Normalized();
    frustum->SetFront(rotationMatrix.MulDir(oldFront));
    vec oldUp = frustum->Up().Normalized();
    frustum->SetUp(rotationMatrix.MulDir(oldUp));
}

void ModuleCamera::RotationZClockwise()
{
    float3x4 rotationMatrix = frustum->WorldMatrix().RotateZ(DEGTORAD * -1);
    //float3x3 rotationMatrix = float3x3::RotateZ(DEGTORAD * -1);
    vec oldFront = frustum->Front().Normalized();
    frustum->SetFront(rotationMatrix.MulDir(oldFront));
    vec oldUp = frustum->Up().Normalized();
    frustum->SetUp(rotationMatrix.MulDir(oldUp));
}

void ModuleCamera::RotationYCounterclockwise()
{
    float3x3 rotationMatrix = float3x3::RotateY(DEGTORAD * 1);
    vec oldFront = frustum->Front().Normalized();
    frustum->SetFront(rotationMatrix.MulDir(oldFront));
    vec oldUp = frustum->Up().Normalized();
    frustum->SetUp(rotationMatrix.MulDir(oldUp));
}

void ModuleCamera::RotationZCounterclockwise()
{
    float3x4 rotationMatrix = frustum->WorldMatrix().RotateZ(DEGTORAD * 1);
    //float3x3 rotationMatrix = float3x3::RotateZ(DEGTORAD * 1);
    vec oldFront = frustum->Front().Normalized();
    frustum->SetFront(rotationMatrix.MulDir(oldFront));
    vec oldUp = frustum->Up().Normalized();
    frustum->SetUp(rotationMatrix.MulDir(oldUp));
}

void ModuleCamera::SetAspectRatio(const float& w, const float& h)
{
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

void ModuleCamera::LookAt(const float& x, const float& y, const float& z)
{
    frustum->SetFront(vec(x, y, z));
}