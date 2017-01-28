#version 330 core
in vec2 passTextureCoord;

// Texture samplers
uniform sampler2D textureSampler;


void main()
{
	gl_FragColor = texture(textureSampler, passTextureCoord);
}