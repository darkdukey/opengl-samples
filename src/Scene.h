#include <memory>
#include <vector>

#include "common.h"

class Node;
class Camera;
class Scene {
   private:
    std::vector<std::shared_ptr<Node>> _children;
    std::shared_ptr<Camera> _camera;

   public:
    Scene();
    ~Scene();
    void addChild(std::shared_ptr<Node> child);
    void addCamera(std::shared_ptr<Camera> camera);
    void draw();
};
