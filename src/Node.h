#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "Graphics.h"
#include "common.h"

class LightManager;
//TODO: change to ECS architecture
class Node : public std::enable_shared_from_this<Node> {
   protected:
    std::shared_ptr<Graphics> _graphics;
    glm::mat4 _transform;
    std::vector<std::shared_ptr<Node>> _children;
    std::shared_ptr<Node> _parent;
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
    static std::shared_ptr<Node> create();
    Node();
    virtual ~Node();
    virtual void update();
    virtual void draw(const glm::mat4& proj, const glm::mat4& view, LightManager* lightMgr);

    std::shared_ptr<Node> getPtr() { return shared_from_this(); }
    std::shared_ptr<Node> getParent() { return _parent; }
    std::shared_ptr<Graphics> getGraphics() const { return _graphics; }
    glm::mat4 getTransform() { return _transform; }
    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);

    void x(float x) { _x = x; }
    void y(float y) { _y = y; }
    void z(float z) { _z = z; }
    float getX() { return _x; }
    float getY() { return _y; }
    float getZ() { return _z; }
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