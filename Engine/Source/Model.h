#pragma once
#include "Mesh.h"
#include "ModuleTexture.h"
#include <vector>
#include "GL/glew.h"
#include "assimp/material.h"

class Model
{
public:
	Model(const char* fileName);
	~Model();
	void Draw();

private:
	void LoadMaterials(aiMaterial** aiMaterial, const unsigned int& numMaterials);
	void LoadMeshes(aiMesh** meshes, const unsigned int& numMeshes);
	std::vector<InfoTexture> materials;
	std::vector<Mesh*> meshes;
};

