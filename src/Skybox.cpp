#include "Skybox.h"

#include <glad/glad.h>

#include <stdexcept>
#include <utility>

#include "stb_image.h"
#include <iostream>
#include <windows.h>


namespace
{
	constexpr float skyboxVertices[] =
	{
		// Back face
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		// Left face
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		// Right face
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		// Front face
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		// Top face
		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		// Bottom face
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
}

Skybox::Skybox(
		const std::vector<std::string>& faces)
	: shader(
			"Assets/Shaders/skybox.vert",
			"Assets/Shaders/skybox.frag"
		)
{
	if (faces.size() != 6)
	{
		throw std::runtime_error(
				"Skybox requires exactly six image paths."
				);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(
			GL_ARRAY_BUFFER,
			VBO
		    );

	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(skyboxVertices),
			skyboxVertices,
			GL_STATIC_DRAW
		    );

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			3 * sizeof(float),
			nullptr
			);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	cubemapTexture = loadCubemap(faces);

	shader.use();
	shader.setInt("skybox", 0);

	glUseProgram(0);
}

Skybox::~Skybox()
{
	if (cubemapTexture != 0)
	{
		glDeleteTextures(
				1,
				&cubemapTexture
				);
	}

	if (VBO != 0)
	{
		glDeleteBuffers(
				1,
				&VBO
			       );
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(
				1,
				&VAO
				);
	}
}


unsigned int Skybox::loadCubemap(
		const std::vector<std::string>& faces)
{
	if (faces.size() != 6)
	{
		throw std::runtime_error(
				"A cubemap requires exactly six textures."
				);
	}

	unsigned int textureID = 0;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	stbi_set_flip_vertically_on_load(false);

	for (unsigned int i = 0; i < faces.size(); ++i)
	{
		std::string message =
			"Loading skybox face:\n" +
			faces[i];

		MessageBoxA(
				nullptr,
				message.c_str(),
				"Skybox Debug",
				MB_OK
			   );

		int width = 0;
		int height = 0;
		int channels = 0;

		unsigned char* data = stbi_load(
				faces[i].c_str(),
				&width,
				&height,
				&channels,
				STBI_rgb
				);

		std::string imageInfo =
			"Loaded:\n" +
			faces[i] +
			"\n\nWidth: " +
			std::to_string(width) +
			"\nHeight: " +
			std::to_string(height);

		MessageBoxA(
				nullptr,
				imageInfo.c_str(),
				"Skybox Face Loaded",
				MB_OK
			   );

		if (!data)
		{
			std::string reason =
				stbi_failure_reason()
				? stbi_failure_reason()
				: "Unknown stb_image error";

			glDeleteTextures(1, &textureID);

			throw std::runtime_error(
					"Failed to load cubemap face: " +
					faces[i] +
					"\nReason: " +
					reason
					);
		}

		glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB8,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			    );

		stbi_image_free(data);
	}

	glTexParameteri(
			GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_MIN_FILTER,
			GL_LINEAR
		       );

	glTexParameteri(
			GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_MAG_FILTER,
			GL_LINEAR
		       );

	glTexParameteri(
			GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_WRAP_S,
			GL_CLAMP_TO_EDGE
		       );

	glTexParameteri(
			GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_WRAP_T,
			GL_CLAMP_TO_EDGE
		       );

	glTexParameteri(
			GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_WRAP_R,
			GL_CLAMP_TO_EDGE
		       );

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}


void Skybox::Draw(
		const glm::mat4& view,
		const glm::mat4& projection) const
{
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);

	shader.use();

	const glm::mat4 rotationOnlyView =
		glm::mat4(glm::mat3(view));

	shader.setMat4(
			"view",
			rotationOnlyView
		      );

	shader.setMat4(
			"projection",
			projection
		      );

	shader.setInt(
			"skybox",
			0
		     );

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(
			GL_TEXTURE_CUBE_MAP,
			cubemapTexture
		     );

	glDrawArrays(
			GL_TRIANGLES,
			0,
			36
		    );

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}
