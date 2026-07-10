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
		void Draw() const;

	private:
		std::vector<Mesh> meshes;
		std::string directory;

		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);	
};

