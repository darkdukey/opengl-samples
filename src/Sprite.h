#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "Node.h"
#include "common.h"

class Sprite : public Node {
   private:
   public:
    static std::shared_ptr<Sprite> create(const std::string& filename);
    Sprite(const std::string& filename);
    ~Sprite();
    void draw(const glm::mat4& proj, const glm::mat4& view) override;

   private:
    void createBuffer();
};
