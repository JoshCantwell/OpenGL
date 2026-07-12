#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform bool hasDiffuseTexture;
uniform vec3 fallbackColor;

void main()
{
	if (hasDiffuseTexture)
	{
		FragColor = texture(texture_diffuse1, TexCoords);
	}
	else
	{
		FragColor = vec4(fallbackColor, 1.0);
	}
}
