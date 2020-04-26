#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "common.h"

class Shader {
   public:
    Shader(const std::string& name);
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void enable();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3Array(const std::string& name, const std::vector<glm::vec3>& value);
    void setMat4(const std::string& name, const glm::mat4& value) const;

   private:
    void init(const std::string& vertexPath, const std::string& fragmentPath);
    uint createShader(const std::string& path, uint type);

   private:
    uint _shaderID;
};
