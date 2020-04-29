#pragma once

#include <string>
#include <unordered_map>

#include "Texture.h"
#include "common.h"

class TextureManager {
   private:
    static TextureManager* s_instance;
    std::unordered_map<std::string, Texture*> _cacheMap;

   public:
    static TextureManager* ins();
    TextureManager();
    ~TextureManager();
    Texture* get(const std::string& name);
};
