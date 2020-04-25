#pragma once

#include <glm/glm.hpp>

#include "Graphics.h"
#include "common.h"
#include "shared_helper.h"
//TODO: change to ECS architecture

class Scene;
class Node : public inheritable_enable_shared_from_this<Node> {
   protected:
    std::shared_ptr<Graphics> _graphics;
    glm::mat4 _transform;
    std::vector<std::shared_ptr<Node>> _children;
    std::shared_ptr<Node> _parent;
    glm::vec3 _pos;
    float _rotX;
    float _rotY;
    float _rotZ;
    float _scaleX;
    float _scaleY;
    float _scaleZ;

   public:
    static std::shared_ptr<Node> create();
    Node();
    virtual ~Node();
    virtual void update();
    virtual void draw();

    virtual void onEnter(Scene* scene);
    virtual void onExit(Scene* scene);

    std::shared_ptr<Node> getPtr() { return shared_from_this(); }
    std::shared_ptr<Node> getParent() { return _parent; }
    std::shared_ptr<Graphics> getGraphics() const { return _graphics; }
    glm::mat4 getTransform() { return _transform; }
    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);

    void position(float x, float y, float z) { _pos = {x, y, z}; }
    glm::vec3 getPosition() { return _pos; }
    void x(float x) { _pos.x = x; }
    void y(float y) { _pos.y = y; }
    void z(float z) { _pos.z = z; }
    float getX() { return _pos.x; }
    float getY() { return _pos.y; }
    float getZ() { return _pos.z; }
    void rotX(float v) { _rotX = v; }
    void rotY(float v) { _rotY = v; }
    void rotZ(float v) { _rotZ = v; }
    void rotByX(float v) { _rotX += v; }
    void rotByY(float v) { _rotY += v; }
    void rotByZ(float v) { _rotZ += v; }
    float getRotX() { return _rotX; }
    float getRotY() { return _rotY; }
    float getRotZ() { return _rotZ; }

   private:
    void setParent(std::shared_ptr<Node> v) { _parent = v; }
};