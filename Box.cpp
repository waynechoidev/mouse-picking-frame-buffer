#include "Box.h"

Box::Box(glm::vec3 size)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;

    // Top
    positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
    positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
    positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
    positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
    normals.push_back(glm::vec3(0.0f, 0.5f, 0.0f));
    normals.push_back(glm::vec3(0.0f, 0.5f, 0.0f));
    normals.push_back(glm::vec3(0.0f, 0.5f, 0.0f));
    normals.push_back(glm::vec3(0.0f, 0.5f, 0.0f));
    texcoords.push_back(glm::vec2(0.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 1.0f));
    texcoords.push_back(glm::vec2(0.0f, 1.0f));

    // Bottom
    positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
    positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
    positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
    positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
    normals.push_back(glm::vec3(0.0f, -0.5f, 0.0f));
    normals.push_back(glm::vec3(0.0f, -0.5f, 0.0f));
    normals.push_back(glm::vec3(0.0f, -0.5f, 0.0f));
    normals.push_back(glm::vec3(0.0f, -0.5f, 0.0f));
    texcoords.push_back(glm::vec2(0.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 1.0f));
    texcoords.push_back(glm::vec2(0.0f, 1.0f));

    // Front
    positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
    positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
    positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
    positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -0.5f));
    texcoords.push_back(glm::vec2(0.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 1.0f));
    texcoords.push_back(glm::vec2(0.0f, 1.0f));

    // Back
    positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
    positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
    positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
    positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, 0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, 0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, 0.5f));
    normals.push_back(glm::vec3(0.0f, 0.0f, 0.5f));
    texcoords.push_back(glm::vec2(0.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 1.0f));
    texcoords.push_back(glm::vec2(0.0f, 1.0f));

    // Left
    positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
    positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
    positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
    positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
    normals.push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
    normals.push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
    normals.push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
    normals.push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
    texcoords.push_back(glm::vec2(0.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 1.0f));
    texcoords.push_back(glm::vec2(0.0f, 1.0f));

    // Right
    positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
    positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
    positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
    positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
    normals.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
    normals.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
    normals.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
    normals.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
    texcoords.push_back(glm::vec2(0.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 0.0f));
    texcoords.push_back(glm::vec2(1.0f, 1.0f));
    texcoords.push_back(glm::vec2(0.0f, 1.0f));

    for (size_t i = 0; i < positions.size(); i++)
    {
        Vertex v;
        v.position = positions[i] * size;
        v.normal = normals[i];
        v.texcoord = texcoords[i];
        _vertices.push_back(v);
    }

    _indices = {
    0,  1,  2,  0,  2,  3,  // Top
    4,  5,  6,  4,  6,  7,  // Bottom
    8,  9,  10, 8,  10, 11, // Front
    12, 13, 14, 12, 14, 15, // Back
    16, 17, 18, 16, 18, 19, // Left
    20, 21, 22, 20, 22, 23  // Right
    };
}
