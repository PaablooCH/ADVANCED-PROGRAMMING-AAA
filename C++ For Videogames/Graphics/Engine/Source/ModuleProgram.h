#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew-2.1.0/include/GL/glew.h"

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

