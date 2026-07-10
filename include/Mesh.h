#pragma once
#include <GLIncludes.h>
#include <vector>

// A single vertex of a mesh
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

// Represents one renderable mesh
class Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&& other) noexcept;
		Mesh& operator=(Mesh&& other) noexcept;

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();

		void Draw() const;

	private:
		unsigned int VAO, VBO, EBO;

		void setupMesh();
};

