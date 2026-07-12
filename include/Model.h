#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model {
	public:
		explicit Model(const std::string& path);
		~Model();

		std::vector<MeshTexture> loadMaterialTextures(
				aiMaterial* material,
				aiTextureType type,
				const std::string& typeName
				);
		unsigned int textureFromFile(
				const std::string& texturePath,
				const std::string& directory
				);
		void Draw(const Shader& shader) const;

	private:
		std::vector<Mesh> meshes;
		std::vector<MeshTexture> texturesLoaded;
		std::string directory;

		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);	
};

