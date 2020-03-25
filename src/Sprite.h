#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "common.h"

class Shader;
class Texture;
class Sprite {
   private:
    Shader* _shader;
    Texture* _texture;
    uint _VAO;
    glm::mat4 _transform;
    float _x;
    float _y;
    float _z;

   public:
    static std::shared_ptr<Sprite> create(const std::string& filename);
    Sprite(const std::string& filename);
    ~Sprite();
    void draw(const glm::mat4& proj, const glm::mat4& view);
    void x(float x) { _x = x; }
    void y(float y) { _y = y; }
    void z(float z) { _z = z; }

   private:
    void createBuffer();
};
