#pragma once

#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "common.h"
#include "types.h"

class DrawCmd {
    glm::mat4 _transform;
    std::string _shaderName;
    //TODO: create material system
    UniformTextureMap _textureUniformMap;
    uint _vao;
    uint _count;
    UniformVec3Map _uniformVec3Map;
    UniformFloatMap _uniformFloatMap;

   public:
    void setTransform(const glm::mat4& t) { _transform = t; }
    glm::mat4& getTransform() { return _transform; }
    std::string getShaderName() { return _shaderName; }
    void setShaderName(const std::string& name) { _shaderName = name; }
    void setTextureUniform(const UniformTextureMap& uniformMap) { _textureUniformMap = uniformMap; }
    UniformTextureMap getTextureUniform() { return _textureUniformMap; }
    void setUniform(const UniformVec3Map& value) { _uniformVec3Map = value; }
    void setUniform(const UniformFloatMap& value) { _uniformFloatMap = value; }
    UniformVec3Map getVec3Uniform() { return _uniformVec3Map; }
    UniformFloatMap getFloatUniform() { return _uniformFloatMap; }
    uint getVAO() { return _vao; }
    void setVAO(uint v) { _vao = v; }
    uint getCount() { return _count; }
    void setCount(uint v) { _count = v; }
};

class Camera;
class LightManager;
class Renderer {
   private:
    static Renderer* s_instance;
    std::vector<DrawCmd> _cmdList;
    uint _count;
    const int INIT_SIZE = 1000;

   private:
    Renderer();
    ~Renderer();

   public:
    static Renderer* ins();
    DrawCmd* getCmd();
    void draw(std::shared_ptr<Camera> cam, LightManager* lightMgr);
};