#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Node.h"
#include "common.h"

enum ProjMode {
    Perspective,
    Orthographic
};

class Camera : public Node {
   private:
    int _width;
    int _height;
    glm::mat4 _proj;
    glm::mat4 _view;
    ProjMode _mode = Perspective;

   public:
    static std::shared_ptr<Camera> create(int width, int height);
    Camera(int width, int height);
    ~Camera();
    void lookat(float x, float y, float z);
    void viewport(int width, int height);
    void setMode(ProjMode mode) { _mode = mode; }
    void pos(float x, float y, float z) override;
    void onAddToScene(Scene* scene) override;
    void onRemoveFromScene(Scene* scene) override;

    glm::mat4& getProj() { return _proj; }
    glm::mat4& getView() { return _view; }

   private:
    void refresh();
};
