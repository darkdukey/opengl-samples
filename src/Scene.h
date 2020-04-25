#pragma once

#include <memory>
#include <vector>

#include "LightManager.h"
#include "common.h"

class Camera;
class Node;
class Scene {
    friend class Light;

   private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<Node> _root;
    LightManager _lightManager;

   private:
    void addLight(std::shared_ptr<Light> light);
    void removeLight(std::shared_ptr<Light> light);

   public:
    static std::shared_ptr<Scene> create();
    Scene();
    ~Scene();
    void addCamera(std::shared_ptr<Camera> camera);
    void addChild(std::shared_ptr<Node> node);
    void removeChild(std::shared_ptr<Node> node);
    void update();
    void draw();
};
