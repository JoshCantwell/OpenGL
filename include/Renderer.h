#pragma once

class Renderer {
	public:
		Renderer();
		~Renderer();

		void draw(float angle, const class Camera& camera);

	private:
		struct GLUquadric* quad;
};

