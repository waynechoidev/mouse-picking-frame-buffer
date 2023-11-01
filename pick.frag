#version 420

out vec4 colour;

uniform vec3 indexColor;

void main()
{
	colour = vec4(indexColor, 1.0);
}