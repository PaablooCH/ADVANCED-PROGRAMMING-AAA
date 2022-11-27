#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleEditor.h"
#include "ModuleTimer.h"
#include "ModuleRenderExercise.h"
#include "Application.h"
#include "MathGeoLib/Math/float3x3.h"
#include "MathGeoLib/Math/float4x4.h"
#include "MathGeoLib/Math/Quat.h"

ModuleCamera::ModuleCamera()
{
    frustum = new Frustum();
    rotateOption = false;
}

bool ModuleCamera::Init()
{
    frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum->SetFrame(float3(0, 2, 8), -float3::unitZ, float3::unitY);
    frustum->SetViewPlaneDistances(0.1f, 100.0f);
    frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT));
    speed = 10.f;
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

void ModuleCamera::RotationX(const float&& multiplier) //TODO unir x e y
{
    float4x4 giro = frustum->WorldMatrix() * float3x3::RotateX(DEGTORAD * speed * multiplier * App->timer->deltaTime);
    frustum->SetFront(giro.MulDir(-float3::unitZ));
    frustum->SetUp(giro.MulDir(float3::unitY));
}

//void ModuleCamera::RotationYObject(const float&& multiplierX, const float&& multiplierY)
//{
//    float3 frontActual = frustum->Front();
//    float3 distancia = (frontActual - centerObject).Normalized();
//    float3 up = frustum->Up();
//
//    Quat RotationX = Quat(up, multiplierY * App->timer->deltaTime * DEGTORAD*0.01);
//    Quat RotationY = Quat(frustum->WorldRight(), multiplierX * App->timer->deltaTime * DEGTORAD*0.01);
//    float3 vectorTransform = RotationX.Transform(distancia);
//    vectorTransform = RotationY.Transform(vectorTransform);
//
//    //float3 vectorTransform = RotationX * distancia + centerObject;
//    //vectorTransform = RotationY * (vectorTransform.Normalized() - centerObject) + centerObject;
//
//    //vectorTransform = vectorTransform.Normalized() * distancia.Length()*5;
//
//    float3 pos = centerObject + vectorTransform;
//
//    float3 front = (centerObject - pos).Normalized();
//    float3 right = Cross(up, front).Normalized();
//    up = Cross(front, right).Normalized();
//    
//    //float3x3 cameraMatrix = float3x3(right, up, front); //Probar con quad
//    frustum->SetFrame(pos, front, up);
//    
//}
 
void ModuleCamera::RotationObject(const float&& multiplierX, const float&& multiplierY)
{
    float3 centerObject = App->exercise->GetModel()->GetCenter();
    // Get orbit point (object transform)
    float3 distance = frustum->Pos() - centerObject;

    // Rotate it
    Quat RotationX = Quat(frustum->Up(), multiplierX * speed * App->timer->deltaTime * DEGTORAD);
    Quat RotationY = Quat(frustum->WorldRight(), multiplierY * speed * App->timer->deltaTime * DEGTORAD);

    // If we look at the object from the bottom or top dont rotate the object
    float cosAngle = Dot(frustum->Front(), float3::unitY);
    if (cosAngle > 0.99f) {
        RotationY = Quat(frustum->WorldRight(), -0.5 * DEGTORAD);
    }
    else if (cosAngle < -0.99f) {
        RotationY = Quat(frustum->WorldRight(), 0.5 * DEGTORAD);
    }

    distance = RotationX.Transform(distance);
    distance = RotationY.Transform(distance);

    // Set camera to where the rotated vector points from its starting position
    frustum->SetPos(distance + centerObject);

    // Look At the object
    LookAt(centerObject);
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

void ModuleCamera::LookAt(float3 lookAt)
{
    float3 direction = lookAt - frustum->Pos();
    // localForward, targetDirection, localUp, worldUp
    float3x3 lookDir = float3x3::LookAt(frustum->Front(), direction.Normalized(), frustum->Up(), float3::unitY);
    frustum->SetFront(lookDir.MulDir(frustum->Front()).Normalized());
    frustum->SetUp(lookDir.MulDir(frustum->Up()).Normalized());
}