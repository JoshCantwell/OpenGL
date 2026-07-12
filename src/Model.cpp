#include <Model.h>
#include <iostream>
#include "Texture.h"
#include <Windows.h>


Model::Model(const std::string& path) {
	loadModel(path);
}

Model::~Model() = default;

void Model::Draw(const Shader& shader) const
{
    for (const auto& mesh : meshes)
    {
        mesh.Draw(shader);
    }
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
			path,
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_GenSmoothNormals
			);

	if (!scene ||
			!scene->mRootNode ||
			(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
	{
		std::string message =
			"ASSIMP ERROR:\n" +
			std::string(importer.GetErrorString());

		MessageBoxA(
				nullptr,
				message.c_str(),
				"Model Loading Error",
				MB_OK | MB_ICONERROR
			   );

		return;
	}

	directory = path.substr(0, path.find_last_of("/\\"));

	meshes.reserve(scene->mNumMeshes);

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
	std::vector<MeshTexture> textures;

	std::cout << "Processing mesh with "
		<< mesh->mNumVertices << " vertices and "
		<< mesh->mNumFaces << " faces."
		<< std::endl;

	// Process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;

		vertex.position = {
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		};

		if (mesh->HasNormals())
		{
			vertex.normal = {
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			};
		}
		else
		{
			vertex.normal = {0.0f, 0.0f, 0.0f};
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoords = {
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			};
		}
		else
		{
			vertex.texCoords = {0.0f, 0.0f};
		}

		vertices.push_back(vertex);
	}

	// Process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// Process material textures
	if (mesh->mMaterialIndex < scene->mNumMaterials)	
	{
		aiMaterial* material =
			scene->mMaterials[mesh->mMaterialIndex];

		std::vector<MeshTexture> diffuseTextures =
			loadMaterialTextures(
					material,
					aiTextureType_DIFFUSE,
					"texture_diffuse"
					);

		textures.insert(
				textures.end(),
				diffuseTextures.begin(),
				diffuseTextures.end()
			       );
	}

	meshes.emplace_back(vertices, indices, textures);
}

std::vector<MeshTexture> Model::loadMaterialTextures(
		aiMaterial* material,
		aiTextureType type,
		const std::string& typeName)
{
	std::vector<MeshTexture> textures;

	MessageBoxA(
			nullptr,
			"Entered loadMaterialTextures",
			"Texture Debug",
			MB_OK
		   );

	unsigned int textureCount = material->GetTextureCount(type);

	std::string countMessage =
		"Texture count: " + std::to_string(textureCount);

	MessageBoxA(
			nullptr,
			countMessage.c_str(),
			"Texture Debug",
			MB_OK
		   );

	for (unsigned int i = 0; i < textureCount; ++i)
	{
		aiString assimpPath;

		if (material->GetTexture(type, i, &assimpPath) != AI_SUCCESS)
		{
			MessageBoxA(
					nullptr,
					"Assimp failed to retrieve texture path",
					"Texture Debug",
					MB_OK
				   );

			continue;
		}

		std::string relativePath = assimpPath.C_Str();

		MessageBoxA(
				nullptr,
				relativePath.c_str(),
				"Assimp texture path",
				MB_OK
			   );

		bool alreadyLoaded = false;

		for (const MeshTexture& loadedTexture : texturesLoaded)
		{
			if (loadedTexture.path == relativePath)
			{
				textures.push_back(loadedTexture);
				alreadyLoaded = true;
				break;
			}
		}

		if (!alreadyLoaded)
		{
			MessageBoxA(
					nullptr,
					"About to call textureFromFile",
					"Texture Debug",
					MB_OK
				   );

			MeshTexture texture;

			texture.id = textureFromFile(relativePath, directory);
			texture.type = typeName;
			texture.path = relativePath;

			if (texture.id != 0)
			{
				textures.push_back(texture);
				texturesLoaded.push_back(texture);
			}
			else
			{
				std::string message =
					"Texture failed to load:\n" + relativePath;

				MessageBoxA(
						nullptr,
						message.c_str(),
						"Texture Error",
						MB_OK | MB_ICONERROR
					   );
			}	
		}
	}

	return textures;
}

unsigned int Model::textureFromFile(
		const std::string& texturePath,
		const std::string& directory)
{
	std::string normalizedPath = texturePath;

	std::replace(
			normalizedPath.begin(),
			normalizedPath.end(),
			'\\',
			'/'
		    );

	std::string fullPath =
		directory + "/" + normalizedPath;

	return LoadTexture(fullPath.c_str());
}
