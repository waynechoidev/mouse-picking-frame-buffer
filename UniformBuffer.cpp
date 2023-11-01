#include "UniformBuffer.h"

UniformBuffer::UniformBuffer()
{
	clear();
	_programID = 0;
	std::cout << "You need a valid program id to generate uniform buffers." << "\n";
}

UniformBuffer::UniformBuffer(GLuint programID)
{
	clear();
	_programID = programID;
}

void UniformBuffer::genVertexBuffers()
{
	glGenBuffers(1, &_uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, _uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 192, nullptr, GL_DYNAMIC_DRAW);
	GLuint matricesBlockIndex = glGetUniformBlockIndex(_programID, "Matrices");
	glUniformBlockBinding(_programID, matricesBlockIndex, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _uboMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::genFragmentBuffers()
{
	glGenBuffers(1, &_uboFragment);
	glBindBuffer(GL_UNIFORM_BUFFER, _uboFragment);
	glBufferData(GL_UNIFORM_BUFFER, 16, nullptr, GL_DYNAMIC_DRAW);
	GLuint fragmentBlockIndex = glGetUniformBlockIndex(_programID, "Fragment");
	glUniformBlockBinding(_programID, fragmentBlockIndex, 1);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _uboFragment);

	glGenBuffers(1, &_uboMaterial);
	glBindBuffer(GL_UNIFORM_BUFFER, _uboMaterial);
	glBufferData(GL_UNIFORM_BUFFER, 16, nullptr, GL_DYNAMIC_DRAW);
	GLuint materialBlockIndex = glGetUniformBlockIndex(_programID, "Material");
	glUniformBlockBinding(_programID, materialBlockIndex, 2);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _uboMaterial);

	glGenBuffers(1, &_uboLight);
	glBindBuffer(GL_UNIFORM_BUFFER, _uboLight);
	glBufferData(GL_UNIFORM_BUFFER, 56, nullptr, GL_DYNAMIC_DRAW);
	GLuint lightBlockIndex = glGetUniformBlockIndex(_programID, "Light");
	glUniformBlockBinding(_programID, lightBlockIndex, 3);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, _uboLight);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::bindVertexBuffers(glm::mat4 model, glm::mat4 projection, glm::mat4 view)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, glm::value_ptr(model));
	glBufferSubData(GL_UNIFORM_BUFFER, 64, 64, glm::value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, 128, 64, glm::value_ptr(projection));
}

void UniformBuffer::bindFragmentBuffers(bool useTexture, glm::vec3 viewPosition, const Material& material, const Light& light)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _uboFragment);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 12, glm::value_ptr(viewPosition));
	int useTextureInt = useTexture ? 1 : 0;
	glBufferSubData(GL_UNIFORM_BUFFER, 12, 4, &useTextureInt);

	glBindBuffer(GL_UNIFORM_BUFFER, _uboMaterial);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 4, &material.ambient);
	glBufferSubData(GL_UNIFORM_BUFFER, 4, 4, &material.shininess);
	glBufferSubData(GL_UNIFORM_BUFFER, 8, 4, &material.diffuse);
	glBufferSubData(GL_UNIFORM_BUFFER, 12, 4, &material.specular);

	glBindBuffer(GL_UNIFORM_BUFFER, _uboLight);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 12, glm::value_ptr(light.position));
	glBufferSubData(GL_UNIFORM_BUFFER, 12, 4, &light.strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 12, glm::value_ptr(light.direction));
	glBufferSubData(GL_UNIFORM_BUFFER, 28, 4, &light.fallOffStart);
	glBufferSubData(GL_UNIFORM_BUFFER, 32, 4, &light.fallOffEnd);
	glBufferSubData(GL_UNIFORM_BUFFER, 36, 4, &light.spotPower);
	glBufferSubData(GL_UNIFORM_BUFFER, 40, 4, &light.isDirectional);
	glBufferSubData(GL_UNIFORM_BUFFER, 44, 4, &light.isPoint);
	glBufferSubData(GL_UNIFORM_BUFFER, 48, 4, &light.isSpot);
	int useBlinnPhongInt = light.useBlinnPhong ? 1 : 0;
	glBufferSubData(GL_UNIFORM_BUFFER, 52, 4, &useBlinnPhongInt);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::clear()
{
	_uboMatrices = _uboFragment = _uboMaterial = _uboLight = 0;
}

UniformBuffer::~UniformBuffer()
{
	clear();
}
