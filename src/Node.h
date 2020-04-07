#pragma once
#include <glm/glm.hpp>
#include "common.h"

class Shader;
class Texture;
class Node {
   private:
    Shader* _shader;
    Texture* _texture;
    uint _VAO;
    glm::mat4 _transform;
    float _x;
    float _y;
    float _z;
    float _rotX;
    float _rotY;
    float _rotZ;
    float _scaleX;
    float _scaleY;
    float _scaleZ;

   public:
    Node();
    virtual ~Node();
    virtual void update();
    virtual void draw(const glm::mat4& proj, const glm::mat4& view){};
};