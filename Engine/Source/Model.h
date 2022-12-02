#pragma once
#include "Mesh.h"
#include "ModuleTexture.h"
#include <vector>
#include "GL/glew.h"
#include "assimp/material.h"
#include "MathGeoLib/Math/float4x4.h"

class Model
{
public:
	Model(const char* fileName);
	~Model();
	void Draw();

	float3 GetCenter() const;

	inline const float3& GetMaxPoints()
	{
		return maxPoint;
	}
	inline const float3& GetMinPoints()
	{
		return minPoint;
	}
	inline const char* GetName()
	{
		return name;
	}

private:
	void LoadMaterials(aiMaterial** aiMaterial, const unsigned int& numMaterials);
	void LoadMeshes(aiMesh** meshes, const unsigned int& numMeshes);
	
	const char* name;

	std::vector<InfoTexture> materials;
	std::vector<Mesh*> meshes;
	float4x4 modelMatrix;

	float3 maxPoint;
	float3 minPoint;
};

