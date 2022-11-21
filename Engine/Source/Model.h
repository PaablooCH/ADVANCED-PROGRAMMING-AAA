#pragma once
#include <vector>
#include "GL/glew.h"

class Model
{
public:
	void Load(const char* fileName);

private:
	void LoadMaterials(const aiScene* scene);
	std::vector<GLint> materials;

};

