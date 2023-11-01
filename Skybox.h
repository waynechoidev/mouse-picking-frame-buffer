#pragma once

#include "Mesh.h"

class Skybox : public Mesh
{
public:
	Skybox() {}
	Skybox(GLfloat scale);

	~Skybox() {}
};
