#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "LightManager.h"
#include "common.h"

class Camera;
class Node;
class Scene {
    friend class Light;
    friend class Camera;
    friend class G;

   private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<Node> _root;
    LightManager _lightManager;
    std::function<void()> _onUpdate;

   private:
    void addLight(std::shared_ptr<Light> light);
    void removeLight(std::shared_ptr<Light> light);
    void addCamera(std::shared_ptr<Camera> camera);
    void removeCamera(std::shared_ptr<Camera> camera);
    void onEnter();
    void onExit();

   public:
    static std::shared_ptr<Scene> create();
    Scene();
    ~Scene();
    void addChild(std::shared_ptr<Node> node);
    void removeChild(std::shared_ptr<Node> node);
    void update();
    void draw();
    void onUpdate(std::function<void()> callback) { _onUpdate = callback; }
};
