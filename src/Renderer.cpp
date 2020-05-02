
#include "Renderer.h"

#include <glad/glad.h>
//Don't reorg
#include "Camera.h"
#include "Debug.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

using namespace std;
using namespace NT;

Renderer::Renderer()
    : _count(0) {
    _cmdList.reserve(INIT_SIZE);
}

Renderer::~Renderer() {
    _cmdList.clear();
}

DrawCmd* Renderer::getCmd() {
    if (_count >= _cmdList.size()) {
        _cmdList.emplace_back();
    }

    LOG(debug) << "Cmd Size: " << _count;
    auto cmd = &_cmdList[_count++];
    cmd->setValid(true);
    return cmd;
}

void Renderer::reset() {
    for (uint i = 0; i < _count; i++) {
        auto& data = _cmdList[i];
        data.setValid(false);
    }
    _count = 0;
}

void Renderer::draw(shared_ptr<Camera> cam, LightManager* lightMgr) {
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (uint i = 0; i < _count; i++) {
        auto& data = _cmdList[i];
        Shader* s = ShaderManager::ins().get(data.getShaderName());
        s->enable();

        // Update Transform
        s->setMat4("transform", data.getTransform());
        s->setMat4("proj", cam->getProj());
        s->setMat4("view", cam->getView());
        s->setVec3("viewPos", cam->worldPos());

        // Set vec3 uniform
        for (auto& it : data.getVec3Uniform()) {
            s->setVec3(it.first, it.second);
        }

        // Set float uniform
        for (auto& it : data.getFloatUniform()) {
            s->setFloat(it.first, it.second);
        }

        // Update Light
        lightMgr->draw(s);

        int c = 0;
        for (auto& it : data.getTextureUniform()) {
            auto tex = TextureManager::ins().get(it.first);
            glActiveTexture(GL_TEXTURE0 + c);
            tex->enable(GL_TEXTURE0 + c);
            s->setInt(it.second, c);
            c++;
        }
        if (c == 0) {
            s->setBool("no_texture", true);
        } else {
            s->setBool("no_texture", false);
        }

        glBindVertexArray(data.getVAO());
        glDrawElements(GL_TRIANGLES, data.getCount(), GL_UNSIGNED_INT, 0);
    }
}
