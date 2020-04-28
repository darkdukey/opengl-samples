#pragma once

#include <glm/glm.hpp>
#include <string>

#include "common.h"

using UniformTextureMap = std::map<std::string, std::string>;
using UniformVec3Map = std::map<std::string, glm::vec3>;
using UniformFloatMap = std::map<std::string, float>;

enum MeshType {
    //Lit object is affected by lighting and use second vec3 as normal
    Lit,
    //Unlit object is not affected by lighting and use second vec3 as color
    Unlit,
    //Solid object is unlit and don't have texture
    Solid
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

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
