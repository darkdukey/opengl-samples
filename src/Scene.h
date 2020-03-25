#include <memory>
#include <vector>

#include "common.h"

class Sprite;
class Camera;
class Scene {
   private:
    std::vector<std::shared_ptr<Sprite>> _children;
    std::shared_ptr<Camera> _camera;

   public:
    Scene();
    ~Scene();
    void addChild(std::shared_ptr<Sprite> child);
    void addCamera(std::shared_ptr<Camera> camera);
    void draw();
};
