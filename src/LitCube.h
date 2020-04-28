#pragma once

#include <memory>

#include "Node.h"
#include "types.h"

class LitCube : public Node {
   private:
   public:
    static std::shared_ptr<LitCube> create(const std::string& shaderName);
    LitCube(const std::string& shaderName);
    ~LitCube();
    void setMaterial(const Material& m);
};