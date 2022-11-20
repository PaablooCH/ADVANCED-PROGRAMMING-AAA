#include "Model.h"
#include "Globals.h"
#include "assimp/ai_assert.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

void Model::Load(const char* fileName)
{
	const aiScene* scene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		// TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);
		// TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", fileName, aiGetErrorString());
	}
}