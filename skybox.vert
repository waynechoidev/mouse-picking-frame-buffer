#version 420

layout (location = 0) in vec3 pos;

out vec3 TexCoords;

layout(std140) uniform Vertices
{
	mat4 model; // 64			0
	mat4 view; // 64			64
	mat4 projection; // 64		128
	// 192
};

void main()
{
	TexCoords = pos;
	gl_Position = projection * view * vec4(pos, 1.0);
}