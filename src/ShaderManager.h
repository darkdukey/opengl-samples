#pragma once
#include <map>
#include <string>

#include "Shader.h"
#include "common.h"

class ShaderManager {
   private:
    std::map<std::string, Shader*> _cacheMap;
    static ShaderManager* s_instance;

   public:
    static ShaderManager* ins();
    ShaderManager();
    ~ShaderManager();
    Shader* get(const std::string& name);
    //TODO: implement LRU
};
