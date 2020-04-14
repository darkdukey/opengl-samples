#include <memory>
#include <vector>

#include "Node.h"
#include "common.h"

class Camera;
class Scene : public Node {
   private:
    std::shared_ptr<Camera> _camera;

   public:
    static std::shared_ptr<Scene> create();
    Scene();
    ~Scene();
    void addCamera(std::shared_ptr<Camera> camera);
    void draw();
};
