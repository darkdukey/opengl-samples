#pragma once

#include <glm/glm.hpp>
#include <string>
#include "common.h"

class Shader {
   public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void enable();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;

   private:
    uint createShader(const std::string& path, GLuint type);

   private:
    uint _shaderID;
};
