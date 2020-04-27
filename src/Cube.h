#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "Node.h"
#include "common.h"

class Cube : public Node {
   private:
   public:
    static std::shared_ptr<Cube> create(const std::string& shaderName);
    static std::shared_ptr<Cube> create(const std::string& shaderName, const std::string& filename);
    Cube(const std::string& shaderName);
    Cube(const std::string& shaderName, const std::string& filename);
    ~Cube();

    void setColorTint(const glm::vec3& color);
};