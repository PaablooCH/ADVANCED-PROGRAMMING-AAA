#include "ModuleCamera.h"
#include "GL/glew.h"
#include "ModuleDebugDraw.h"
#include "ModuleEditor.h"
#include "ModuleTimer.h"
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
    speed = 10;
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

void ModuleCamera::RotationY(const float&& multiplier)
{
    float4x4 giro = float3x3::RotateY(DEGTORAD * speed * multiplier * App->timer->deltaTime) * frustum->WorldMatrix();
    frustum->SetFront(giro.MulDir(-float3::unitZ));
    frustum->SetUp(giro.MulDir(float3::unitY));
}

void ModuleCamera::RotationX(const float&& multiplier) //TODO multiplier +/-
{
    float4x4 giro = frustum->WorldMatrix() * float3x3::RotateX(DEGTORAD * speed * multiplier * App->timer->deltaTime);
    frustum->SetFront(giro.MulDir(-float3::unitZ));
    frustum->SetUp(giro.MulDir(float3::unitY));
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

void ModuleCamera::LookAt(const float& x, const float& y, const float& z)
{
    frustum->SetFront(vec(x, y, z));
}