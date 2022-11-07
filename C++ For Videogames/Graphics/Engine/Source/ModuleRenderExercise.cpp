#include "ModuleRenderExercise.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "GL/glew.h"
#include "MathGeoLib/Math/float4x4.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include <iostream>

ModuleRenderExercise::ModuleRenderExercise()
{
	program = 0;
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	program = App->program->CreateProgram();

	frustum = new Frustum();
	frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	frustum->SetFrame(float3(0,4,8), -float3::unitZ, float3::unitY);
	frustum->SetViewPlaneDistances(0.1f, 100.0f);
	frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90, aspect);

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	float4x4 model, view, proj;
	model = float4x4::FromTRS(	float3(2.0f, 0.0f, 0.0f),
								float4x4::RotateZ(pi / 4.0f),
								float3(2.0f, 1.0f, 1.0f));
	view = frustum->ViewMatrix();
	proj = frustum->ProjectionMatrix();

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &proj[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

	App->debugdraw->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo);
	delete frustum;
	return true;
}
