#pragma once
#include <vector>
#include "GL/glew.h"
#include "Mesh.h"
#include "ModuleTexture.h"

class Model
{
public:
	void Load(const char* fileName);

private:
	void LoadMaterials(aiMaterial** aiMaterial, const unsigned int& numMaterials);
	void LoadMeshes(aiMesh** _meshes, const unsigned int& _numMeshes);
	std::vector<InfoTexture> materials;
	std::vector<InfoVBO> vbos;
	std::vector<InfoEBO> ebos;

};

