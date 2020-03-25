#include <glm/glm.hpp>

#include "common.h"

class Shader;
class Texture;
class Sprite {
   private:
    Shader* _shader;
    Texture* _texture;
    uint _VAO;
    glm::mat4 _transform;
    float _x;
    float _y;
    float _z;

   public:
    Sprite(const std::string& filename);
    ~Sprite();
    void draw();
    void x(float x) { _x = x; }
    void y(float y) { _y = y; }
    void z(float z) { _z = z; }

   private:
    void createBuffer();
};
