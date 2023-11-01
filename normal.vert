#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;

layout(std140) uniform Vertices
{
	mat4 model; // 64			0
	mat4 view; // 64		64
	mat4 projection; // 64			128
	// 192
};

void main()
{
    vec4 position = vec4(pos, 1.0);


    // compute Normal first
    vec3 normalWorld = normalize(mat3(transpose(inverse(model))) * norm);
    
    position = projection * view * model * position;
    
    float t = tex.x;
    
    position.xyz += normalWorld * t * 0.2;

    gl_Position = position;    

}