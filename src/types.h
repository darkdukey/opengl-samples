#pragma once

#include <glm/glm.hpp>
#include <string>

#include "common.h"

using UniformTextureMap = std::map<std::string, std::string>;
using UniformVec3Map = std::map<std::string, glm::vec3>;
using UniformFloatMap = std::map<std::string, float>;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // // tangent
    // glm::vec3 Tangent;
    // // bitangent
    // glm::vec3 Bitangent;
    Vertex() {}
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv)
        : Position(px, py, pz), Normal(nx, ny, nz), TexCoords(tu, tv) {
    }
};
