#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "Graphics.h"
#include "Node.h"
#include "common.h"

class Sprite : public Node {
   private:
   public:
    static std::shared_ptr<Sprite> create(const std::string& filename);
    Sprite(const std::string& filename);
    ~Sprite();
};
