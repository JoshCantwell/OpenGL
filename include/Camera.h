#pragma once

class Camera {
	public:
		float camX = 20.0f, camY = 20.0f, camZ = 15.0f;
		float yaw = 0.0f, pitch = 0.0f;

		float velocityY = 1.0f;     // vertical velocity
		float gravity = -0.01f;     // gravitational acceleration
		bool grounded = false;
		float floorY = -1.0f;       // floor height


		float getDirX() const { return dirX; }
		float getDirY() const { return dirY; }
		float getDirZ() const { return dirZ; }

		void update(const class Input& input, float speed);
		void applyView() const;

	private:
		float dirX, dirY, dirZ;
};

