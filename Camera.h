#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera(glm::vec3 startPosition, glm::vec3 startUp, glm::vec3 startFront);

	glm::vec3 getPosition();
	GLfloat* getRotation() { return &_rotate.x; }
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 _startPosition, _position;
	glm::vec3 _startFront, _front;
	glm::vec3 _startUp, _up;

	glm::vec3 _rotate;

	void update();
};

