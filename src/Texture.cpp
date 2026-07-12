#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include "Texture.h"
#include <Windows.h>
#include <string>

unsigned int LoadTexture(const char* path)
{
	int width = 0;
	int height = 0;
	int channels = 0;

	unsigned char* data =
		stbi_load(path, &width, &height, &channels, 0);

	if (!data)
	{
		std::string message =
			std::string("Failed to load texture:\n") +
			path +
			"\n\nReason:\n" +
			stbi_failure_reason();

		MessageBoxA(
				nullptr,
				message.c_str(),
				"Texture Loading Error",
				MB_OK | MB_ICONERROR
			   );

		return 0;
	}

	GLenum format = GL_RGB;

	if (channels == 1)
	{
		format = GL_RED;
	}
	else if (channels == 3)
	{
		format = GL_RGB;
	}
	else if (channels == 4)
	{
		format = GL_RGBA;
	}
	else
	{
		stbi_image_free(data);

		MessageBoxA(
				nullptr,
				"Unsupported texture channel count",
				"Texture Loading Error",
				MB_OK | MB_ICONERROR
			   );

		return 0;
	}

	unsigned int textureID = 0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			format,
			width,
			height,
			0,
			format,
			GL_UNSIGNED_BYTE,
			data
		    );

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_S,
			GL_REPEAT
		       );

	glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_T,
			GL_REPEAT
		       );

	glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR
		       );

	glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER,
			GL_LINEAR
		       );

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	return textureID;
}


Texture::Texture(){


}

Texture::~Texture(){


}
