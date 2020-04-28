#pragma once

#include <map>
#include <string>
#include <vector>

#include "common.h"
#include "types.h"

class Texture;
class DrawCmd;
class Graphics {
   private:
    // Shader* _shader;
    std::map<std::string, Texture*> _textures;
    UniformTextureMap _textureUniformMap;
    UniformVec3Map _vec3Map;
    UniformFloatMap _floatMap;
    uint _VAO;
    uint _indexSize;
    DrawCmd* _cmd;
    Material _mat;

   public:
    Graphics(const std::string& shader_name);
    ~Graphics();
    // Shader* getShader() const { return _shader; }
    void addTexture(const std::string& name, const std::string& type = "texture0");
    void draw(const glm::mat4& transform);
    void createBuffer(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
    void setUniform(const std::string& name, glm::vec3 value);
    void setUniform(const std::string& name, float value);
    void setMaterial(const Material& m);
};
