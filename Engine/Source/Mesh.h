#pragma once
#include <assimp/mesh.h>
#include "GL/glew.h"

struct InfoVBO
{
	GLint vbo;
	int numVertices;
};

struct InfoEBO
{
	GLint ebo;
	int numIndices;
};

class Mesh
{
public:
	void static LoadVBO(const aiMesh* mesh, InfoVBO& info);
	void static LoadEBO(const aiMesh* mesh, InfoEBO& info);
};

