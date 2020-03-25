#include <map>
#include <string>
#include "common.h"

class Shader;

class ShaderManager {
   private:
    std::map<std::string, Shader*> _cacheMap;
    static ShaderManager* s_instance;

   public:
    static ShaderManager* getInstance();
    ShaderManager();
    ~ShaderManager();
    Shader* get(const std::string& name);
    //TODO: implement LRU
};
