#pragma once
#include <glm/glm.hpp>

class Node {
   private:
   public:
    Node() {}
    virtual ~Node() {}
    virtual void draw(const glm::mat4& proj, const glm::mat4& view){};
};