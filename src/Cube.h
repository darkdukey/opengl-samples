#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "Node.h"
#include "common.h"
class Shader;
class Texture;
class Cube : public Node {
   private:
    Shader* _shader;
    Texture* _texture;
    uint _VAO;
    glm::mat4 _transform;
    float _x;
    float _y;
    float _z;

   public:
    Cube(const std::string& filename);
    ~Cube();
    static std::shared_ptr<Cube> create(const std::string& filename);
    void draw(const glm::mat4& proj, const glm::mat4& view) override;
    void x(float x) { _x = x; }
    void y(float y) { _y = y; }
    void z(float z) { _z = z; }

   private:
    void createBuffer();
};