#pragma once
#include <assimp/mesh.h>
#include "ModuleTexture.h"
#include "GL/glew.h"

class Mesh
{
public:
	Mesh(const aiMesh* mesh);
	~Mesh();
	void Draw(const std::vector<InfoTexture>& model_textures);
	
private:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();

	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	int numVertices;
	int numIndices;
	int materialIindex;
};

