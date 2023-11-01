#include "Cubemap.h"

#include "stb_image.h"

Cubemap::Cubemap()
{
	_textureID = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
}

void Cubemap::initialise(std::vector<std::string> faceLocations)
{
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

	int width, height, bitDepth;

	for (size_t i = 0; i < 6; i++)
	{
		unsigned char* texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);
		if (texData)
		{
			glTexImage2D((GLenum)GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			stbi_image_free(texData);
		}
		else
		{
			std::cout << "Failed to find :" << faceLocations[i].c_str() << "\n";
			return;
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
}

void Cubemap::clear()
{
	glDeleteTextures(1, &_textureID);
	_textureID = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
}

Cubemap::~Cubemap()
{
	clear();
}