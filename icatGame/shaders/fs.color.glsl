#version 330 core
in vec3 vsColor;

out vec4 out_color;

void main()
{
	out_color = vec4(vsColor, 1.0f);
}