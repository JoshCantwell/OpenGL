#include <Camera.h>
#include <Input.h>
#include <cmath>
#include <gl/GLU.h>

void Camera::update(const Input& input) {
    // Mouse-based look
    float sensitivity = 0.15f;
    yaw   += input.getMouseDeltaX() * sensitivity;
    pitch -= input.getMouseDeltaY() * sensitivity;

    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    float radYaw = yaw * 3.14159f / 180.0f;
    float radPitch = pitch * 3.14159f / 180.0f;

    dirX = cos(radPitch) * sin(radYaw);
    dirY = sin(radPitch);
    dirZ = -cos(radPitch) * cos(radYaw);

    float len = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    dirX /= len; dirY /= len; dirZ /= len;

    float speed = 0.05f;
    if (input.keyDown('W')) {
        camX += dirX * speed;
        camY += dirY * speed;
        camZ += dirZ * speed;
    }
    if (input.keyDown('S')) {
        camX -= dirX * speed;
        camY -= dirY * speed;
        camZ -= dirZ * speed;
    }
    if (input.keyDown('A')) {
        camX += cos(radYaw) * speed;
        camZ += sin(radYaw) * speed;
    }
    if (input.keyDown('D')) {
        camX -= cos(radYaw) * speed;
        camZ -= sin(radYaw) * speed;
    }

    // Collision
    if (camY >= floorY) {
        camY -= 0.5f;
    }
}

void Camera::applyView() const {
    gluLookAt(
        camX, camY, camZ,
        camX + dirX, camY + dirY, camZ + dirZ,
        0.0f, 1.0f, 0.0f
    );
}
