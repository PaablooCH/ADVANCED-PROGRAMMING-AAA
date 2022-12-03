#pragma once
#include <assimp/mesh.h>
#include "ModuleTexture.h"
#include "MathGeoLib/Math/float3.h"
#include "GL/glew.h"

class Mesh
{
public:
	Mesh(const aiMesh* mesh);
	~Mesh();
	void Draw(const std::vector<InfoTexture>& model_textures);

	inline const int& GetNumVertices() {
		return numVertices;
	}
	inline const int& GetNumIndices() {
		return numVertices;
	}
	inline const int& GetMaterialIndex() {
		return materialIndex;
	}
	float3 max;
	float3 min;
	
private:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();

	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	int numVertices;
	int numIndices;
	int materialIndex;
};

