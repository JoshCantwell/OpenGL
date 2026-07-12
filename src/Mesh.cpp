#include "Mesh.h"
#include <utility>


Mesh::Mesh(Mesh&& other) noexcept
: vertices(std::move(other.vertices)),
	indices(std::move(other.indices)),
	textures(std::move(other.textures)),
	VAO(other.VAO),
	VBO(other.VBO),
	EBO(other.EBO)
{
	other.VAO = 0;
	other.VBO = 0;
	other.EBO = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other)
    {
        if (VAO != 0)
            glDeleteVertexArrays(1, &VAO);

        if (VBO != 0)
            glDeleteBuffers(1, &VBO);

        if (EBO != 0)
            glDeleteBuffers(1, &EBO);

        vertices = std::move(other.vertices);
        indices = std::move(other.indices);
        textures = std::move(other.textures);

        VAO = other.VAO;
        VBO = other.VBO;
        EBO = other.EBO;

        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }

    return *this;
}


Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices ,const std::vector<MeshTexture>& textures)
	: vertices(vertices), indices(indices), textures(textures)
{
	setupMesh();
}

Mesh::~Mesh()
{
	if (VAO != 0)
		glDeleteVertexArrays(1, &VAO);

	if (VBO != 0)
		glDeleteBuffers(1, &VBO);

	if (EBO != 0)
		glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// Vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(const Shader& shader) const
{
	bool hasDiffuseTexture = false;
	unsigned int diffuseNumber = 1;

	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		if (textures[i].type != "texture_diffuse")
			continue;

		hasDiffuseTexture = true;

		glActiveTexture(GL_TEXTURE0 + i);

		std::string uniformName =
			"texture_diffuse" +
			std::to_string(diffuseNumber);

		shader.setInt(
				uniformName,
				static_cast<int>(i)
			     );

		glBindTexture(
				GL_TEXTURE_2D,
				textures[i].id
			     );

		++diffuseNumber;
	}

	shader.setBool(
			"hasDiffuseTexture",
			hasDiffuseTexture
		      );

	shader.setVec3(
			"fallbackColor",
			glm::vec3(0.8f, 0.4f, 0.1f)
		      );

	glBindVertexArray(VAO);

	glDrawElements(
			GL_TRIANGLES,
			static_cast<GLsizei>(indices.size()),
			GL_UNSIGNED_INT,
			nullptr
		      );

	glBindVertexArray(0);

	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glActiveTexture(GL_TEXTURE0);
}
