#include "Model.h"
#include <iostream>


Model::Model(const std::string& path) {
	loadModel(path);
}

Model::~Model() = default;

void Model::Draw() const {
	for (const auto& mesh : meshes)
		mesh.Draw();
}

void Model::loadModel(const std::string& path)
{

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
			path,
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_GenNormals
			);



	directory = path.substr(0, path.find_last_of("/\\"));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{

	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{

		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];


		processMesh(mesh, scene);	

	}


	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}

}

void Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;


	std::cout << "Processing mesh with "
		<< mesh->mNumVertices << " vertices and "
		<< mesh->mNumFaces << " faces."
		<< std::endl;

	// Process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;
		vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

		if (mesh->HasNormals())
			vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		else
			vertex.normal = { 0.0f, 0.0f, 0.0f };

		if (mesh->mTextureCoords[0])
			vertex.texCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		else
			vertex.texCoords = { 0.0f, 0.0f };

		vertices.push_back(vertex);
	}

	// Process faces (indices)
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	meshes.emplace_back(vertices, indices);	
}

