#pragma once

#include <iostream>
#include "Common.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class UniformBuffer
{
public:
	UniformBuffer();
	UniformBuffer(GLuint programID);

	void genVertexBuffers();
	void genFragmentBuffers();
	void bindVertexBuffers(glm::mat4 model, glm::mat4 projection, glm::mat4 view);
	void bindFragmentBuffers(bool useTexture, glm::vec3 viewPosition, const Material& material, const Light& light);

	~UniformBuffer();
private:
	GLuint _programID;
	GLuint _uboMatrices, _uboFragment, _uboMaterial, _uboLight;
	
	void clear();
};

