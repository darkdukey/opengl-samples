#pragma once

#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "common.h"
#include "types.h"

class DrawCmd {
    GETSET(glm::mat4, transform, Transform)
    GETSETR(std::string, shaderName, ShaderName)
    GETSET(uint, vao, VAO)
    GETSET(uint, count, Count)
    GETSETB(bool, valid, Valid)
    GETSETB(bool, useDepth, UseDepth)
    GETSETR(UniformTextureMap, textureUniformMap, TextureUniform)
    GETR(UniformVec3Map, uniformVec3Map, Vec3Uniform)
    GETR(UniformFloatMap, uniformFloatMap, FloatUniform)

   public:
    DrawCmd() : _valid(false){};

    void setUniform(const UniformVec3Map& value) { _uniformVec3Map = value; }
    void setUniform(const UniformFloatMap& value) { _uniformFloatMap = value; }
};

class Camera;
class LightManager;
class Renderer {
    friend class Graphics;
    friend class G;

   private:
    std::vector<DrawCmd> _cmdList;
    uint _count;
    const int INIT_SIZE = 1000;

   private:
    Renderer();
    ~Renderer();
    DrawCmd* getCmd();
    void reset();

   public:
    static Renderer&
    ins() {
        static Renderer r{};
        return r;
    };
    void draw(std::shared_ptr<Camera> cam, LightManager* lightMgr);
};