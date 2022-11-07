#include "ModuleCamera.h"
#include "GL/glew.h"
#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"
#include "Application.h"

ModuleCamera::ModuleCamera()
{
}

bool ModuleCamera::Init()
{
    frustum = new Frustum();
    frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
    aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
    frustum->SetFrame(float3(0, 4, 8), -float3::unitZ, float3::unitY);
    frustum->SetViewPlaneDistances(0.1f, 100.0f);
    frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90, aspect);
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

void ModuleCamera::SetFOV(int deg)
{
    frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * deg, aspect);
}

void ModuleCamera::SetAspectRatio(int w, int h)
{
    aspect = w / h;
    frustum->SetHorizontalFovAndAspectRatio(frustum->HorizontalFov(), aspect);
}

void ModuleCamera::SetPlaneDistances()
{
}

void ModuleCamera::Position()
{
}

void ModuleCamera::Orientation()
{
}

void ModuleCamera::LookAt(int x, int y, int z)
{
}
