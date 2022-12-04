#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "Model.h"
#include "SDL.h"

ModuleRender::ModuleRender()
{
	colorGrid = float3(0.501961f, 0.501961f, 0.501961f);
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
	context = SDL_GL_CreateContext(App->window->window);

	//LOG_ENGINE("Creating Renderer context");
	App->editor->logs.emplace_back("Creating Renderer context");

	GLenum err = glewInit();
	LOG_ENGINE("Using Glew %s", glewGetString(GLEW_VERSION));

	LOG_ENGINE("Vendor: %s", glGetString(GL_VENDOR));
	LOG_ENGINE("Renderer: %s", glGetString(GL_RENDERER));
	LOG_ENGINE("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG_ENGINE("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glDisable(GL_SCISSOR_TEST); // Not going to use scissor test for now
	glDisable(GL_STENCIL_TEST); // Not going to use stencil test for now
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	return true;
}

bool ModuleRender::Start()
{
	program = App->program->CreateProgram();
	model = new Model("Models/Bakerhouse.fbx");
	return true;
}

update_status ModuleRender::PreUpdate()
{
	int h, w;
	SDL_GetWindowSize(App->window->window, &w, &h);
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backgroundRGBA[0], backgroundRGBA[1], backgroundRGBA[2], backgroundRGBA[3]);
	App->debugdraw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), SCREEN_WIDTH, SCREEN_HEIGHT, colorGrid);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	model->Draw();
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	//LOG_ENGINE("Destroying renderer");
	App->editor->logs.emplace_back("Destroying renderer");

	glDeleteProgram(program);
	delete model;
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	App->camera->SetAspectRatio(float(width), float(height));
}

void ModuleRender::DropFile(const char* pathFile)
{
	delete model;
	model = new Model(pathFile);
}
