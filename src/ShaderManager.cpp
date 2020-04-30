#include "ShaderManager.h"

#include "Shader.h"

using namespace std;

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
    for (auto& it : _cacheMap) {
        delete it.second;
    }

    _cacheMap.clear();
}

Shader* ShaderManager::get(const string& name) {
    if (_cacheMap.find(name) != _cacheMap.end()) {
        return _cacheMap[name];
    } else {
        Shader* shader = new Shader(name);
        _cacheMap[name] = shader;
        return shader;
    }
}
