#pragma once
#include <glm/glm.hpp>
#include "common.h"

class Shader;
class Texture;
class Node {
   protected:
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
    void x(float x) { _x = x; }
    void y(float y) { _y = y; }
    void z(float z) { _z = z; }
    float getX() {return _x;}
    float getY() {return _y;}
    float getZ() {return _z;}
    void rotX(float v) { _rotX = v;}
    void rotY(float v) { _rotY = v;}
    void rotZ(float v) { _rotZ = v;}
    float getRotX() {return _rotX;}
    float getRotY() {return _rotY;}
    float getRotZ() {return _rotZ;}
};