
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

Renderer* Renderer::s_instance = nullptr;

Renderer* Renderer::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new Renderer();
    }

    return s_instance;
}

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

    return &_cmdList[_count++];
}

void Renderer::draw(shared_ptr<Camera> cam, LightManager* lightMgr) {
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (uint i = 0; i < _count; i++) {
        auto data = _cmdList[i];
        Shader* s = ShaderManager::getInstance()->get(data.getShaderName());
        s->enable();

        // Update Transform
        s->setMat4("transform", data.getTransform());
        s->setMat4("proj", cam->getProj());
        s->setMat4("view", cam->getView());

        // Update Light
        s->setVec3(lightMgr->NameAmbientColor, lightMgr->getAmbientColor());

        int c = 0;
        for (auto& it : data.getUniformMap()) {
            auto tex = TextureManager::getInstance()->get(it.first);
            glActiveTexture(GL_TEXTURE0 + c);
            tex->enable(GL_TEXTURE0 + c);
            s->setInt(it.second, c);
            c++;
        }

        glBindVertexArray(data.getVAO());
        glDrawElements(GL_TRIANGLES, data.getCount(), GL_UNSIGNED_INT, 0);
    }
}
