#include "ModuleCamera.h"
#include "GL/glew.h"
#include "ModuleDebugDraw.h"
#include "Application.h"

ModuleCamera::ModuleCamera()
{
}

bool ModuleCamera::Init()
{
    frustum = new Frustum();
    frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum->SetFrame(float3(0, 4, 8), -float3::unitZ, float3::unitY);
    frustum->SetViewPlaneDistances(0.1f, 100.0f);
    frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90, SCREEN_WIDTH / SCREEN_HEIGHT);
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
    frustum->SetPos(pos);
}

void ModuleCamera::Orientation(const vec& up)
{
    frustum->SetUp(up);
}

void ModuleCamera::LookAt(const float& x, const float& y, const float& z)
{
    frustum->SetFront(vec(x, y, z));
}
