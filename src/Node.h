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
    glm::vec3 _rot;
    glm::vec3 _scale;
    Scene* _scene;

   public:
    static std::shared_ptr<Node> create();
    Node();
    virtual ~Node();
    virtual void update();
    virtual void draw();

    virtual void onAddToScene(Scene* scene);
    virtual void onRemoveFromScene(Scene* scene);

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
    void rotX(float v) { _rot.x = v; }
    void rotY(float v) { _rot.y = v; }
    void rotZ(float v) { _rot.z = v; }
    void rotByX(float v) { _rot.x += v; }
    void rotByY(float v) { _rot.y += v; }
    void rotByZ(float v) { _rot.z += v; }
    float getRotX() { return _rot.x; }
    float getRotY() { return _rot.y; }
    float getRotZ() { return _rot.z; }

   private:
    void setParent(std::shared_ptr<Node> v) { _parent = v; }
};