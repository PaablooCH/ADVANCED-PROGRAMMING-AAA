#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();
	int CreateProgram();

private:
	char* LoadShaderSource(const char* shader_file_name);
	int CompileShader(GLenum type, const char* source);
	
};

