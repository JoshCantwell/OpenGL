#pragma once

#include <glm.hpp>

class Renderer {
	public:
		Renderer();
		~Renderer();

		void draw(float angle, const class Camera& camera, const glm::vec3& sphereColor );

	private:
		struct GLUquadric* quad;
};

