#include "Program.h"

Program::Program()
{
	_programID = 0;
	clear();
}

void Program::createFromString(std::string vertexCode, std::string fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Program::createFromFiles(std::string vertexLocation, std::string fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Program::readFile(std::string fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation.c_str(), std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Failed to read %s! File doesn't exist." << fileLocation;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Program::compileShader(std::string vertexCode, std::string fragmentCode)
{
	_programID = glCreateProgram();

	if (!_programID)
	{
		std::cout << "Error creating shader program!\n";
		return;
	}

	addShader(_programID, vertexCode, GL_VERTEX_SHADER);
	addShader(_programID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(_programID);
	glGetProgramiv(_programID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(_programID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: '%s'\n" << eLog;
		return;
	}

	glValidateProgram(_programID);
	glGetProgramiv(_programID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(_programID, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: '%s'\n" << eLog;
		return;
	}
}

void Program::use()
{
	glUseProgram(_programID);
}
void Program::clear()
{
	if (_programID != 0)
	{
		glDeleteProgram(_programID);
		_programID = 0;
	}

}

void Program::addShader(GLuint theProgram, std::string shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode.c_str();

	GLint codeLength[1];
	codeLength[0] = (GLint)strlen(shaderCode.c_str());

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the %d shader: '%s'\n" << shaderType << eLog;
		return;
	}

	glAttachShader(theProgram, theShader);
}

Program::~Program()
{
	clear();
}

