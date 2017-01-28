#version 330 core

in vec2 passTextureCoord;

uniform sampler2D textureSampler;

void main(void){
	gl_FragColor = texture(textureSampler, passTextureCoord);
}