#include "../include/ObjLoader.h"
#include "../include/glad/glad.h"
#include "../include/RenderComponent.h"


ObjLoader::ObjLoader(){


}

ObjLoader::~ObjLoader(){

	

}

glm::vec2 ObjLoader::read_vec2(std::vector<std::string> words){

	return glm::vec2(std::stof(words[1]), std::stof(words[2]));

}


glm::vec3 ObjLoader::read_vec3(std::vector<std::string> words){

	return glm::vec3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));

}

void ObjLoader::make_obj_mesh(const char* filename){

	std::vector<glm::vec3> v;
	std::vector<glm::vec2> vt;
	std::vector<glm::vec3> vn;
	std::vector<float> vertices;

	size_t vertexCount = 0;
	size_t texcoodCount = 0;
	size_t normalCount = 0;
	size_t triangleCount = 0;

	std::vector<std::string> words;
	std::string line;

	// First pass: open and count
	{
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Failed to open OBJ file: " << filename << std::endl;
			return;
		}

		while (std::getline(file, line)) {
			words = Split(line, " ");
			if (words.empty()) continue;

			if (words[0] == "v") {
				++vertexCount;
			} else if (words[0] == "vt") {
				++texcoodCount;
			} else if (words[0] == "vn") {
				++normalCount;
			} else if (words[0] == "f") {
				triangleCount += words.size() - 3;
			}
		}
		// file closes here at end of scope
	}

	// Reserve memory
	v.reserve(vertexCount);
	vt.reserve(texcoodCount);
	vn.reserve(normalCount);
	vertices.reserve(triangleCount * 3 * 8); // 3 verts per triangle, 8 floats per vert

	// Second pass: open again fresh and parse
	{
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Failed to reopen OBJ file: " << filename << std::endl;
			return;
		}

		while (std::getline(file, line)) {
			words = Split(line, " ");
			if (words.empty()) continue;

			if (words[0] == "v") {
				v.push_back(read_vec3(words));
			} else if (words[0] == "vt") {
				vt.push_back(read_vec2(words));
			} else if (words[0] == "vn") {
				vn.push_back(read_vec3(words));
			} else if (words[0] == "f") {
				read_face(words, v, vt, vn, vertices);
			}
		}
		// file closes here at end of scope
	}

//	std::cout << "\tPositions: " << v.size() << std::endl;
//	std::cout << "\tTexcoords: " << vt.size() << std::endl;
//	std::cout << "\tNormals:   " << vn.size() << std::endl;
//	std::cout << "\tTriangles: " << triangleCount << std::endl;

}


void ObjLoader::make_obj(glm::vec3 position, glm::vec3 eulers){

	make_obj_mesh("../assets/Cube.obj");

	
}

void ObjLoader::read_face(std::vector<std::string> words, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, std::vector<glm::vec3>& vn, std::vector<float>& vertices){



	size_t triangleCount = words.size() - 3;
	for (size_t i = 0; i < triangleCount; ++i) {


		read_corner(words[1], v, vt, vn, vertices);
		read_corner(words[2 + i], v, vt, vn, vertices);
		read_corner(words[3 + i], v, vt, vn, vertices);

	}

}

void ObjLoader::read_corner(std::string description, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, std::vector<glm::vec3>& vn, std::vector<float>& vertices){

	std::vector<std::string> v_vt_vn = Split(description, "/");

	/// Position
	glm::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
	vertices.push_back(pos[0]);
	vertices.push_back(pos[1]);
	vertices.push_back(pos[2]);

	/// Tex coord
	glm::vec2 tex = v[std::stol(v_vt_vn[1]) - 1];
	vertices.push_back(pos[0]);
	vertices.push_back(pos[1]);

	/// position
	glm::vec3 normal = v[std::stol(v_vt_vn[2]) - 1];
	vertices.push_back(pos[0]);
	vertices.push_back(pos[1]);
	vertices.push_back(pos[2]);
}


std::vector<std::string> ObjLoader::Split(std::string line, std::string delimiter) {

	std::vector<std::string> splitLine;

	size_t pos = 0;
	std::string token;
	while((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0,pos);
		splitLine.push_back(token);
		line.erase(0, pos + delimiter.length());
	}
	splitLine.push_back(line);

	return splitLine;
}
