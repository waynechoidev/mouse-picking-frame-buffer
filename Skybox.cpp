#include "Skybox.h"

Skybox::Skybox(GLfloat scale)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;

    positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f) * scale);
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f) * scale);
    positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f) * scale);

    positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f) * scale);
    positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f) * scale);
    positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f) * scale);
    positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f) * scale);

    for (int i = 0; i < positions.size(); i++)
    {
        normals.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        texcoords.push_back(glm::vec2(0.0f, 0.0f));
    }

    for (size_t i = 0; i < positions.size(); i++)
    {
        Vertex v;
        v.position = positions[i];
        v.normal = normals[i];
        v.texcoord = texcoords[i];
        _vertices.push_back(v);
    }

    _indices = {
    0,  1,  2,  2,  1,  3,  // Front
    2,  3,  5,  5,  3,  7,  // Right
    5,  7,  4,  4,  7,  6, // Back
    4,  6,  0,  0,  6,  1, // Left
    4,  0,  5,  5,  0,  2, // Top
    1,  6,  3,  3,  6,  7  // Bottom
    };
}
