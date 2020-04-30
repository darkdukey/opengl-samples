#pragma once

#include <string>
#include <unordered_map>

#include "Texture.h"
#include "common.h"

class TextureManager {
   private:
    std::unordered_map<std::string, Texture*> _cacheMap;

   public:
    static TextureManager& ins() {
        static TextureManager t{};
        return t;
    };
    TextureManager();
    ~TextureManager();
    Texture* get(const std::string& name);
};
