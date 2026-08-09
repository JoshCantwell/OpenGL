#include "Terrain.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <Texture.h>

#include "stb_image.h"


Terrain::Terrain(
		const std::string& heightmapPath,
		float worldSize,
		float heightScale)
	: worldSize(worldSize),
	heightScale(heightScale)
{
	if (!loadHeightmap(heightmapPath))
	{
		throw std::runtime_error(
				"Failed to load terrain heightmap: " +
				heightmapPath
				);
	}

	buildMesh();
}


bool Terrain::loadHeightmap(
		const std::string& path)
{
	int channels = 0;

	unsigned char* data = stbi_load(
			path.c_str(),
			&mapWidth,
			&mapHeight,
			&channels,
			1
			);

	if (!data)
	{
		std::cerr
			<< "Failed to load heightmap: "
			<< path
			<< '\n';

		std::cerr
			<< "stb_image error: "
			<< stbi_failure_reason()
			<< '\n';

		return false;
	}

	heights.resize(
			static_cast<std::size_t>(mapWidth) *
			static_cast<std::size_t>(mapHeight)
		      );

	for (int z = 0; z < mapHeight; ++z)
	{
		for (int x = 0; x < mapWidth; ++x)
		{
			const int index =
				z * mapWidth + x;

			const unsigned char pixel =
				data[index];

			const float normalized =
				static_cast<float>(pixel) /
				255.0f;

			heights[index] =
				(normalized - 0.5f) *
				heightScale;
		}
	}

	stbi_image_free(data);

	std::cout
		<< "Heightmap loaded: "
		<< mapWidth
		<< " x "
		<< mapHeight
		<< '\n';

	return true;
}


float Terrain::getHeight(
		int x,
		int z) const
{
	x = std::clamp(
			x,
			0,
			mapWidth - 1
		      );

	z = std::clamp(
			z,
			0,
			mapHeight - 1
		      );

	return heights[
		z * mapWidth + x
	];
}


glm::vec3 Terrain::calculateNormal(
		int x,
		int z) const
{
	const float heightLeft =
		getHeight(x - 1, z);

	const float heightRight =
		getHeight(x + 1, z);

	const float heightDown =
		getHeight(x, z - 1);

	const float heightUp =
		getHeight(x, z + 1);

	glm::vec3 normal(
			heightLeft - heightRight,
			2.0f,
			heightDown - heightUp
			);

	return glm::normalize(normal);
}


void Terrain::buildMesh()
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<MeshTexture> textures;

	MeshTexture grassTexture;

	grassTexture.id =
		LoadTexture(
				"Assets/Terrain/Dirt.jpg"
			   );

	grassTexture.type =
		"texture_diffuse";

	grassTexture.path =
		"Assets/Terrain/Dirt.jpg";

	if (grassTexture.id != 0)
	{
		textures.push_back(grassTexture);
	}

	vertices.reserve(
			static_cast<std::size_t>(mapWidth) *
			static_cast<std::size_t>(mapHeight)
			);

	const float halfSize =
		worldSize * 0.5f;
	const float textureRepeat = 32.0f;


	for (int z = 0; z < mapHeight; ++z)
	{
		for (int x = 0; x < mapWidth; ++x)
		{
			const float normalizedX =
				static_cast<float>(x) /
				static_cast<float>(mapWidth - 1);

			const float normalizedZ =
				static_cast<float>(z) /
				static_cast<float>(mapHeight - 1);


			Vertex vertex;

			vertex.position =
			{
				normalizedX * worldSize - halfSize,
				getHeight(x, z),
				normalizedZ * worldSize - halfSize
			};

			vertex.normal =
				calculateNormal(x, z);

			vertex.texCoords =
			{
				normalizedX * textureRepeat,
				normalizedZ * textureRepeat
			};

			vertices.push_back(vertex);
		}
	}


	indices.reserve(
			static_cast<std::size_t>(mapWidth - 1) *
			static_cast<std::size_t>(mapHeight - 1) *
			6
		       );

	for (int z = 0; z < mapHeight - 1; ++z)
	{
		for (int x = 0; x < mapWidth - 1; ++x)
		{
			const unsigned int topLeft =
				z * mapWidth + x;

			const unsigned int topRight =
				topLeft + 1;

			const unsigned int bottomLeft =
				(z + 1) * mapWidth + x;

			const unsigned int bottomRight =
				bottomLeft + 1;

			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);

			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}


	mesh = std::make_unique<Mesh>(
			vertices,
			indices,
			textures
			);

	std::cout
		<< "Terrain created: "
		<< vertices.size()
		<< " vertices, "
		<< indices.size() / 3
		<< " triangles."
		<< '\n';
}


void Terrain::Draw(
		const Shader& shader) const
{
	if (!mesh)
	{
		return;
	}

	mesh->Draw(shader);
}
