#include "ModuleRenderExercise.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "GL/glew.h"

ModuleRenderExercise::ModuleRenderExercise()
{
	program = 0;
	vbo = 0;
	vao = 0;
	tbo = 0;
	ebo = 0;
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	return true;
}

bool ModuleRenderExercise::Start()
{
	program = App->program->CreateProgram();
	float vtx_data[] = {	 // positions         // texture coords
							 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
							 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
							-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
							-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	//ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// load & create texture
	InfoTexture info;
	App->texture->LoadTexture("Baboon.png", info);
	tbo = info.id;
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
	view = App->camera->GetViewMatrix();
	proj = App->camera->ProjectionMatrix();

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &proj[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, tbo);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ebo);
	glDeleteTextures(1, &tbo);
	return true;
}
