#pragma once

#include "Common.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

class Program
{
public:
	Program();

	void createFromString(std::string vertexCode, std::string fragmentCode);
	void createFromFiles(std::string vertexLocation, std::string fragmentLocation);

	std::string readFile(std::string fileLocation);

	void use();

	GLuint getID() { return _programID; }

	~Program();

private:
	GLuint _programID;

	void compileShader(std::string vertexCode, std::string fragmentCode);
	void addShader(GLuint theProgram, std::string shaderCode, GLenum shaderType);
	void clear();
};
