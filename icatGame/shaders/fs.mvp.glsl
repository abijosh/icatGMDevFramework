#version 330 core
in vec2 passTextureCoord;

// Texture samplers
uniform sampler2D textureSampler;

out vec4 outColor;

void main()
{
	outColor = texture(textureSampler, passTextureCoord);
}