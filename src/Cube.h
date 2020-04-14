#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "Node.h"
#include "common.h"

class Cube : public Node {
   private:
   public:
    static std::shared_ptr<Cube> create(const std::string& filename);
    Cube(const std::string& filename);
    ~Cube();
};