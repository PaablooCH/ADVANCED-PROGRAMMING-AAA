#include "ModuleProgram.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}

int ModuleProgram::CompileShader(GLenum type, const char* source)
{
	unsigned shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, 0);
	glCompileShader(shaderId);
	int res = GL_FALSE;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shaderId, len, &written, info);
			LOG_ENGINE("Log Info: %s", info);
			free(info);
		}
	}
	return shaderId;
}

int ModuleProgram::CreateProgram()
{
	int fragment = CompileShader(GL_FRAGMENT_SHADER, LoadShaderSource("fragmentShader.glsl"));
	int vertex = CompileShader(GL_VERTEX_SHADER, LoadShaderSource("vertexShader.glsl"));

	unsigned programId = glCreateProgram();
	glAttachShader(programId, vertex);
	glAttachShader(programId, fragment);
	glLinkProgram(programId);
	int res;
	glGetProgramiv(programId, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(programId, len, &written, info);
			LOG_ENGINE("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return programId;
}
