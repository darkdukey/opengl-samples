#include "TextureManager.h"

#include "Texture.h"

using namespace std;

TextureManager* TextureManager::s_instance = nullptr;
TextureManager* TextureManager::ins() {
    if (s_instance == nullptr) {
        s_instance = new TextureManager();
    }
    return s_instance;
}

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
    for (auto& it : _cacheMap) {
        delete it.second;
    }

    _cacheMap.clear();
}

Texture* TextureManager::get(const string& name) {
    if (_cacheMap.find(name) != _cacheMap.end()) {
        return _cacheMap[name];
    } else {
        Texture* tex = new Texture(name);
        _cacheMap[name] = tex;
        return tex;
    }
}
