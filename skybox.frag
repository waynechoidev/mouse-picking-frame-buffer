#version 420

in vec3 TexCoords;

out vec4 colour;

layout(binding=0) uniform samplerCube skybox;
layout(binding=1) uniform samplerCube diffuseCubemap; 

void main()
{
	colour = texture(skybox, TexCoords);
}