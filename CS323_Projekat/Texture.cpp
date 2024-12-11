#include <iostream>
#include "stb_image.h"
#include "Texture.h"

Texture::Texture(GLenum textureTarget, const std::string& fileName)
	:
	textureTarget(textureTarget),
	fileName(fileName)
{
}

bool Texture::Load()
{
	//STB loads images from top to bottom, in OpenGL its bottom to top
	stbi_set_flip_vertically_on_load(1);

	int width = 0, height = 0, nOfChannels = 0;

	//bpp - bits per pixel of texture image, 0 loads all channels, retrieves address of texture data
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &nOfChannels, 0);

	if (!imageData)
	{
		printf("Cant load texture from '%s' - %s\n", fileName.c_str(), stbi_failure_reason);
		exit(0);
	}
	
	printf("Successfuly loaded. Width %d, height %d, bpp %d\n", width, height, nOfChannels);

	//Generate texture object(ID), stores it in textureObj
	glGenTextures(1, &textureObj);

	//Bind the texture
	glBindTexture(textureTarget, textureObj);

	if (textureTarget == GL_TEXTURE_2D)
	{
		//Generate an actual texture
		glTexImage2D(textureTarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(textureTarget);
	}

	glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(textureTarget, 0);

	stbi_image_free(imageData);

	return true;
}

void Texture::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(textureTarget, textureObj);
}
