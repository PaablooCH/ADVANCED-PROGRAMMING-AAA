#include "ModuleCamera.h"
#include "GL/glew.h"
#include "ModuleDebugDraw.h"
#include "Application.h"
#include "MathGeoLib/Math/float3x3.h"
#include "MathGeoLib/Math/float4x4.h"

ModuleCamera::ModuleCamera()
{
    frustum = new Frustum();
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

void ModuleCamera::MoveForward(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Front() * 0.1f * multiplier * App->deltaTime);
}

void ModuleCamera::MoveBackward(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Front() * -0.1f * multiplier * App->deltaTime);
}

void ModuleCamera::MoveLeft(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->WorldRight() * -0.1f * multiplier * App->deltaTime);
}

void ModuleCamera::MoveRight(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->WorldRight() * 0.1f * multiplier * App->deltaTime);
}

void ModuleCamera::GoUp(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * .1f * multiplier * App->deltaTime);
}

void ModuleCamera::GoDown(const float&& multiplier)
{
    frustum->SetPos(frustum->Pos() + frustum->Up().Normalized() * -.1f * multiplier * App->deltaTime);
}

void ModuleCamera::RotationYClockwise(const float&& multiplier)
{
    float4x4 giro = frustum->WorldMatrix() * float3x3::RotateY(DEGTORAD * -1 * multiplier * App->deltaTime);
    frustum->SetFront(giro.MulDir(-float3::unitZ));
    frustum->SetUp(giro.MulDir(float3::unitY));
}

void ModuleCamera::RotationXClockwise(const float&& multiplier)
{
    float4x4 giro = frustum->WorldMatrix() * float3x3::RotateX(DEGTORAD * 1 * multiplier * App->deltaTime);
    frustum->SetFront(giro.MulDir(-float3::unitZ));
    frustum->SetUp(giro.MulDir(float3::unitY));
}

void ModuleCamera::RotationYCounterclockwise(const float&& multiplier)
{
    float4x4 giro = frustum->WorldMatrix() * float3x3::RotateY(DEGTORAD * 1 * multiplier * App->deltaTime);
    frustum->SetFront(giro.MulDir(-float3::unitZ));
    frustum->SetUp(giro.MulDir(float3::unitY));
}

void ModuleCamera::RotationXCounterclockwise(const float&& multiplier)
{
    float4x4 giro = frustum->WorldMatrix()* float3x3::RotateX(DEGTORAD * -1 * multiplier * App->deltaTime);
    frustum->SetFront(giro.MulDir(-float3::unitZ));
    frustum->SetUp(giro.MulDir(float3::unitY));
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