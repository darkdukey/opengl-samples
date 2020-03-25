#include <glm/glm.hpp>

#include "common.h"

enum ProjMode {
    Perspective,
    Orthographic
};

class Camera {
   private:
    int _width;
    int _height;
    glm::mat4 _proj;
    glm::mat4 _view;
    glm::vec3 _pos;
    ProjMode _mode = Perspective;

   public:
    Camera(int width, int height);
    ~Camera();
    void position(float x, float y, float z);
    void lookat(float x, float y, float z);
    void viewport(int width, int height);
    void setMode(ProjMode mode) { _mode = mode; }

    glm::mat4& getProj() { return _proj; }
    glm::mat4& getView() { return _view; }

   private:
    void refresh();
};
