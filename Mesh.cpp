#include "Mesh.h"

Mesh::Mesh()
{
	_VAO = 0;
	_VBO = 0;
	_IBO = 0;
	_indexCount = 0;
	_indexColor = std::vector<unsigned char>(3, 0);
}

void Mesh::initialise()
{
	_indexCount = (GLsizei)_indices.size();
	int vertexDataSize = sizeof(_vertices[0].position[0]) * 8;

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _indices.size(), _indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexDataSize, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexDataSize, (void*)(sizeof(_vertices[0].position[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexDataSize, (void*)(sizeof(_vertices[0].position[0]) * 6));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::setIndexColor(unsigned char r, unsigned char g, unsigned char b)
{
	_indexColor[0] = r;
	_indexColor[1] = g;
	_indexColor[2] = b;
}

bool Mesh::checkIndexColor(unsigned char* color)
{
	if (color[0] == _indexColor[0] && color[1] == _indexColor[1] && color[2] == _indexColor[2]) return true;
	else return false;
}

void Mesh::clear()
{
	if (_IBO != 0)
	{
		glDeleteBuffers(1, &_IBO);
		_IBO = 0;
	}

	if (_VBO != 0)
	{
		glDeleteBuffers(1, &_VBO);
		_VBO = 0;
	}

	if (_VAO != 0)
	{
		glDeleteVertexArrays(1, &_VAO);
		_VAO = 0;
	}

	_indexCount = 0;
}


Mesh::~Mesh()
{
	clear();
}

