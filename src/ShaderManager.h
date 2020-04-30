#pragma once
#include <map>
#include <string>

#include "Shader.h"
#include "common.h"

class ShaderManager {
   private:
    std::map<std::string, Shader*> _cacheMap;

   public:
    static ShaderManager& ins() {
        static ShaderManager s{};
        return s;
    };
    ShaderManager();
    ~ShaderManager();
    Shader* get(const std::string& name);
    //TODO: implement LRU
};
