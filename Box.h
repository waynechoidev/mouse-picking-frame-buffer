#pragma once

#include "Mesh.h"

class Box : public Mesh
{
public:
	Box(glm::vec3 size);
	Box() :Box(glm::vec3(1.0f)) {}

	~Box() {}
};

