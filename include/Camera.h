#pragma once

class Camera {
	public:
		float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
		float yaw = 0.0f, pitch = 0.0f;

		float velocityY = 1.0f;     // vertical velocity
		float gravity = -0.01f;     // gravitational acceleration
		bool grounded = false;
		float floorY = -1.0f;       // floor height



		void update(const class Input& input, float speed);
		void applyView() const;

	private:
		float dirX, dirY, dirZ;
};

