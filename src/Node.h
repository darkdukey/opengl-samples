#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
    // World
    glm::vec3 _worldScale;
    glm::quat _worldRot;
    glm::vec3 _worldPos;
    glm::vec3 _worldSkew;
    glm::vec4 _perspective;

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

    virtual void pos(float x, float y, float z) { _pos = {x, y, z}; }
    glm::vec3 getPosition() { return _pos; }
    glm::vec3 getWorldPos() { return _worldPos; };
    void sx(float x) { _pos.x = x; }
    void sy(float y) { _pos.y = y; }
    void sz(float z) { _pos.z = z; }
    float x() { return _pos.x; }
    float y() { return _pos.y; }
    float z() { return _pos.z; }
    void srx(float v) { _rot.x = v; }
    void sry(float v) { _rot.y = v; }
    void srz(float v) { _rot.z = v; }
    void srbx(float v) { _rot.x += v; }
    void srby(float v) { _rot.y += v; }
    void srbz(float v) { _rot.z += v; }
    float rx() { return _rot.x; }
    float ry() { return _rot.y; }
    float rz() { return _rot.z; }
    void sscale(float x, float y, float z) { _scale = {x, y, z}; }

   private:
    void setParent(std::shared_ptr<Node> v) { _parent = v; }
};