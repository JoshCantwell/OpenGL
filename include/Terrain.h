#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"

class Terrain
{
	public:
		Terrain(
				const std::string& heightmapPath,
				float worldSize,
				float heightScale
		       );

		~Terrain() = default;

		Terrain(const Terrain&) = delete;
		Terrain& operator=(const Terrain&) = delete;

		Terrain(Terrain&&) noexcept = default;
		Terrain& operator=(Terrain&&) noexcept = default;

		void Draw(const Shader& shader) const;

	private:
		int mapWidth = 0;
		int mapHeight = 0;

		float worldSize = 100.0f;
		float heightScale = 15.0f;

		std::vector<float> heights;

		std::unique_ptr<Mesh> mesh;

		bool loadHeightmap(
				const std::string& path
				);

		void buildMesh();

		float getHeight(
				int x,
				int z
			       ) const;

		glm::vec3 calculateNormal(
				int x,
				int z
				) const;
};
