#pragma once

#include <GL/glew.h>
#include <string>

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	GLuint getTextureID(std::string  texFileName);

};