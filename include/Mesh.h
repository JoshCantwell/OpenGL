#pragma once
#include <GLIncludes.h>
#include <vector>
#include <string>
#include <Shader.h>

// A single vertex of a mesh
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct MeshTexture {

	unsigned int id = 0;
	std::string type;
	std::string path;

};



// Represents one renderable mesh
class Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<MeshTexture> textures;

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&& other) noexcept;
		Mesh& operator=(Mesh&& other) noexcept;

		Mesh(
				const std::vector<Vertex>& vertices,
				const std::vector<unsigned int>& indices,
				const std::vector<MeshTexture>& textures
		    );
		~Mesh();

		void Draw(const Shader& shader) const;

	private:
		unsigned int VAO, VBO, EBO;

		void setupMesh();
};

