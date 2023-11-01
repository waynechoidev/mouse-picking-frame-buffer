#pragma once

#include <GL\glew.h>
#include "Common.h"
#include <vector>

class Mesh
{
public:
	Mesh();

	void initialise();
	void draw();

	void setIndexColor(unsigned char r, unsigned char g, unsigned char b);
	std::vector<unsigned char> getIndexColor() { return _indexColor; }
	bool checkIndexColor(unsigned char* color);

	~Mesh();

protected:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;

private:
	GLuint _VAO, _VBO, _IBO;
	GLsizei _indexCount;

	std::vector<unsigned char> _indexColor;

	void clear();
};

