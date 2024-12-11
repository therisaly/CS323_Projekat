#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

#endif 

class Texture
{
public:
	Texture(GLenum textureTarget, const std::string& fileName);
	bool Load();
	void Bind(GLenum textureUnit);
private:
	std::string fileName;
	GLenum textureTarget;
	GLuint textureObj;
};
