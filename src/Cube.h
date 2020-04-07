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
   public:
    Cube(const std::string& filename);
    ~Cube();
    static std::shared_ptr<Cube> create(const std::string& filename);
    void draw(const glm::mat4& proj, const glm::mat4& view) override;

   private:
    void createBuffer();
};