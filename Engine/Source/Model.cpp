#include "Model.h"
#include "Mesh.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"
#include "Globals.h"
#include "assimp/ai_assert.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

Model::Model(const char* file)
{
	std::string pathFile = std::string(file);
	const size_t lastSlashIdx = pathFile.find_last_of("\\/");
	std::string relativePath = pathFile.substr(0, lastSlashIdx + 1);
	if (std::string::npos != lastSlashIdx)
	{
		pathFile.erase(0, lastSlashIdx + 1);
	}
	// Remove extension if present.
	const size_t periodIdx = pathFile.rfind('.');
	bool extension = pathFile.substr(periodIdx) == ".fbx" ? true : false;
	const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality);
	if (extension && scene)
	{
		LoadMaterials(scene->mMaterials, scene->mNumMaterials, relativePath.c_str());
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);

		modelMatrix = float4x4::identity;

		//Get name model
		if (std::string::npos != periodIdx)
		{
			pathFile.erase(periodIdx); //Get name
		}
		name = pathFile;
		App->camera->PosCameraViewObject(this);
	}
	else if (!extension) {
		App->editor->logs.emplace_back("Extension File not supported. Only supported fbx extension.");
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", file, aiGetErrorString());
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

void Model::LoadMaterials(aiMaterial** aiMaterial, const unsigned int& numMaterials, const char* pathFbx)
{
	aiString file;
	materials.reserve(numMaterials);
	App->editor->logs.emplace_back("Loading textures.");

	for (unsigned i = 0; i < numMaterials; ++i)
	{
		if (aiMaterial[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			InfoTexture info;
			LOG_ENGINE("Assimp: Loading the texture %i", i);
			std::string nameTexture = std::string(file.data);
			if (App->texture->LoadTexture(nameTexture.c_str(), info)) {
				materials.push_back(info);
				continue;
			}
			const size_t lastSlashIdx = nameTexture.find_last_of("\\/");
			if (std::string::npos != lastSlashIdx)
			{
				nameTexture.erase(0, lastSlashIdx + 1);
			}
			std::string  texturePath = pathFbx + nameTexture;
			if (App->texture->LoadTexture(texturePath.c_str(), info)) {
				materials.push_back(info);
				continue;
			}
			texturePath = "Textures/" + nameTexture;
			
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
	App->editor->logs.emplace_back("Meshes loaded.");

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
	CalculateCenter();
}

void Model::CalculateCenter()
{
	center = float3(minPoint.x + (maxPoint.x - minPoint.x) / 2.0f,
		minPoint.y + (maxPoint.y - minPoint.y) / 2.0f,
		minPoint.z + (maxPoint.z - minPoint.z) / 2.0f);
}
