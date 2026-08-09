#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include <iostream>
#include <windows.h>

#include "Texture.h"

unsigned int LoadTexture(const char* path)
{
	if (path == nullptr || path[0] == '\0')
	{
		MessageBoxA(
				nullptr,
				"LoadTexture received an empty path.",
				"Texture Error",
				MB_OK | MB_ICONERROR
			   );

		return 0;
	}

	/*MessageBoxA(
			nullptr,
			path,
			"LoadTexture Path",
			MB_OK
		   );*/

	int width = 0;
	int height = 0;
	int originalChannels = 0;

	/*MessageBoxA(
			nullptr,
			"About to call stbi_load",
			"Texture Debug",
			MB_OK
		   );*/

	// Force every image to RGBA.
	unsigned char* data = stbi_load(
			path,
			&width,
			&height,
			&originalChannels,
			STBI_rgb_alpha
			);

	if (data == nullptr)
	{
		const char* reason = stbi_failure_reason();

		std::string message =
			"Failed to load texture:\n" +
			std::string(path) +
			"\n\nReason:\n" +
			(reason ? reason : "Unknown stb_image error");

		MessageBoxA(
				nullptr,
				message.c_str(),
				"Texture Load Error",
				MB_OK | MB_ICONERROR
			   );

		return 0;
	}

	/*std::string imageInfo =
		"Image successfully decoded.\n\nWidth: " +
		std::to_string(width) +
		"\nHeight: " +
		std::to_string(height) +
		"\nOriginal channels: " +
		std::to_string(originalChannels);

	MessageBoxA(
			nullptr,
			imageInfo.c_str(),
			"Texture Information",
			MB_OK
		   );*/

	unsigned int textureID = 0;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// RGBA rows are always multiples of four bytes.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	/*MessageBoxA(
			nullptr,
			"About to call glTexImage2D",
			"Texture Debug",
			MB_OK
		   );*/

	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA8,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data
		    );

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::string message =
			"glTexImage2D error code: " +
			std::to_string(error);

		MessageBoxA(
				nullptr,
				message.c_str(),
				"OpenGL Texture Error",
				MB_OK | MB_ICONERROR
			   );

		glDeleteTextures(1, &textureID);
		stbi_image_free(data);

		return 0;
	}

	/*MessageBoxA(
			nullptr,
			"glTexImage2D returned successfully",
			"Texture Debug",
			MB_OK
		   );*/

	glGenerateMipmap(GL_TEXTURE_2D);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::string message =
			"glGenerateMipmap error code: " +
			std::to_string(error);

		MessageBoxA(
				nullptr,
				message.c_str(),
				"OpenGL Texture Error",
				MB_OK | MB_ICONERROR
			   );
	}

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

	/*MessageBoxA(
			nullptr,
			"Texture completely loaded",
			"Texture Debug",
			MB_OK
		   );*/

	return textureID;
}


Texture::Texture(){


}

Texture::~Texture(){


}
