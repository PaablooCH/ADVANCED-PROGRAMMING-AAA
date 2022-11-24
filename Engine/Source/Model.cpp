#include "assimp/ai_assert.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "Model.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleEditor.h"
#include "Globals.h"

Model::Model(const char* fileName)
{
	const aiScene* scene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", fileName, aiGetErrorString());
	}
}

Model::~Model()
{
	for (int i = 0; i < materials.size(); i++) {
		glDeleteTextures(1, &materials[i].id);
	}

	for (int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
	}
}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->Draw(materials);
	}
}

void Model::LoadMaterials(aiMaterial** aiMaterial, const unsigned int& numMaterials)
{
	aiString file;
	materials.reserve(numMaterials);
	App->editor->logs.emplace_back("Loading textures.");

	for (unsigned i = 0; i < numMaterials; ++i)
	{
		if (aiMaterial[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			LOG_ENGINE("Assimp: Loading the texture %i", i);
			InfoTexture info;
			App->texture->LoadTexture(file.data, info);
			materials.push_back(info);
		}
	}
}

void Model::LoadMeshes(aiMesh** aiMesh, const unsigned int& numMeshes)
{
	App->editor->logs.emplace_back("Assimp: Loading the meshes");
	meshes = std::vector<Mesh*>(numMeshes);
	App->editor->logs.emplace_back("Loading meshes.");

	for (unsigned int i = 0; i < numMeshes; ++i)
	{
		LOG_ENGINE("Assimp: Loading the mesh %i", i);
		meshes[i] = new Mesh(aiMesh[i]);
	}
}
