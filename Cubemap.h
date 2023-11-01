#pragma once

#include <iostream>
#include <vector>
#include <GL\glew.h>

class Cubemap
{
public:
	Cubemap();

	void initialise(std::vector<std::string> faceLocations);
	void use();
	void clear();

	~Cubemap();

private:
	GLuint _textureID;
	int _width, _height, _bitDepth;
};