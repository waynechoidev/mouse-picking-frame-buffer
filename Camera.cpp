#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, glm::vec3 startFront)
{
    _startPosition = _position = startPosition;
    _startUp = _up = startUp;
    _startFront = _front = startFront;

    _rotate = glm::vec3(0.0f, 0.0f, 0.0f);
    update();
}

void Camera::update()
{
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, _rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, _rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
    //rotationMatrix = glm::rotate(rotationMatrix, _rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));

    _position = glm::vec3(rotationMatrix * glm::vec4(_startPosition, 1.0f));
    _front = glm::vec3(rotationMatrix * glm::vec4(_startFront, 1.0f));
    _up = glm::vec3(rotationMatrix * glm::vec4(_startUp, 1.0f));
}


glm::vec3 Camera::getPosition()
{
    update();
    return _position;
}

glm::mat4 Camera::calculateViewMatrix()
{
    update();
    return glm::lookAt(_position, _position + _front, _up);
}

Camera::~Camera() {}