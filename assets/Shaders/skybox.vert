#version 330 core

layout (location = 0) in vec3 aPosition;

out vec3 TextureDirection;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	TextureDirection = aPosition;

	vec4 clipPosition =
		projection *
		view *
		vec4(aPosition, 1.0);

	// Force skybox depth to the far plane.
	gl_Position = clipPosition.xyww;
}
