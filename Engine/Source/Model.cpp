#include "Model.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleEditor.h"
#include "Globals.h"
#include "assimp/ai_assert.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

Model::Model(const char* fileName)
{
	std::string pathFile = std::string(fileName);
	const size_t lastSlashIdx = pathFile.find_last_of("\\/");
	if (std::string::npos != lastSlashIdx)
	{
		pathFile.erase(0, lastSlashIdx + 1);
	}
	// Remove extension if present.
	const size_t periodIdx = pathFile.rfind('.');
	bool extension = pathFile.substr(periodIdx) == ".fbx" ? true : false;
	if (std::string::npos != periodIdx)
	{
		pathFile.erase(periodIdx);
	}
	name = pathFile.c_str();
	const aiScene* scene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality);
	if (extension && scene)
	{
		LoadMaterials(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);

		modelMatrix = float4x4::identity;
		//for (int i = 0; i < meshes.size(); ++i) {

		//}
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

float3 Model::GetCenter() const
{
	return float3(minPoint.x + (maxPoint.x - minPoint.x) / 2.0f, //TODO Aplicar Transformaciones del objeto
		minPoint.y + (maxPoint.y - minPoint.y) / 2.0f, 
		minPoint.z + (maxPoint.z - minPoint.z) / 2.0f);
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
			std::string texturePath = std::string(file.data);
			const size_t lastSlashIdx = texturePath.find_last_of("\\/");
			if (std::string::npos != lastSlashIdx)
			{
				texturePath.erase(0, lastSlashIdx + 1);
			}
			texturePath = "Textures/" + texturePath;

			LOG_ENGINE("Assimp: Loading the texture %i", i);
			InfoTexture info;
			App->texture->LoadTexture(texturePath.c_str(), info);
			materials.push_back(info);
		}
	}
}

void Model::LoadMeshes(aiMesh** aiMesh, const unsigned int& numMeshes)
{
	meshes = std::vector<Mesh*>(numMeshes);
	App->editor->logs.emplace_back("Loading meshes.");

	for (unsigned int i = 0; i < numMeshes; ++i)
	{
		LOG_ENGINE("Assimp: Loading the mesh %i", i);
		meshes[i] = new Mesh(aiMesh[i]);
	}

	minPoint = meshes[0]->min;
	maxPoint = meshes[0]->max;
	for (unsigned int i = 0; i < numMeshes; ++i)
	{
		if (maxPoint.x < meshes[i]->max.x) maxPoint.x = meshes[i]->max.x;
		if (minPoint.x > meshes[i]->min.x) minPoint.x = meshes[i]->min.x;
		
		if (maxPoint.y < meshes[i]->max.y) maxPoint.y = meshes[i]->max.y;
		if (minPoint.y > meshes[i]->min.y) minPoint.y = meshes[i]->min.y;
		
		if (maxPoint.z < meshes[i]->max.z) maxPoint.z = meshes[i]->max.z;
		if (minPoint.z > meshes[i]->min.z) minPoint.z = meshes[i]->min.z;
	}
}
