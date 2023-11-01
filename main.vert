#version 420

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;

out vec3 posWorld;
out vec3 normalWorld;
out vec2 TexCoord;
out vec3 posModel;

layout(std140) uniform Vertices
{
	mat4 model; // 64			0
	mat4 view; // 64			64
	mat4 projection; // 64		128
	// 192
};

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	posWorld = (model * vec4(pos, 1.0)).xyz;
	
	// ignore scale
	normalWorld = normalize(mat3(transpose(inverse(model))) * norm);
	TexCoord = tex;
	posModel = pos;
}