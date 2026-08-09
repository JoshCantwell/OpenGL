#pragma once
#include <Shader.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>


class Skybox
{
	public:
		Skybox(const std::vector<std::string>& faces);
		~Skybox();

		Skybox(const Skybox&) = delete;
		Skybox& operator=(const Skybox&) = delete;

		Skybox(Skybox&& other) noexcept;
		Skybox& operator=(Skybox&& other) noexcept;

		void Draw(
				const glm::mat4& view,
				const glm::mat4& projection
			 ) const;

	private:
		unsigned int VAO = 0;
		unsigned int VBO = 0;
		unsigned int cubemapTexture = 0;

		int currentSkybox = 1;

		Shader shader;

		unsigned int loadCubemap(
				const std::vector<std::string>& faces
				);
};
