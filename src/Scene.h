#pragma once

#include <memory>
#include <vector>

#include "LightManager.h"
#include "Node.h"
#include "common.h"

class Camera;
class Scene : public Node {
   private:
    std::shared_ptr<Camera> _camera;
    LightManager _lightManager;

   public:
    static std::shared_ptr<Scene> create();
    Scene();
    ~Scene();
    void addCamera(std::shared_ptr<Camera> camera);
    void draw();

    void addLight(std::shared_ptr<Light> light);
};
