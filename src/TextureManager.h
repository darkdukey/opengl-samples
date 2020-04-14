#include <map>
#include <string>

#include "Texture.h"
#include "common.h"

class TextureManager {
   private:
    static TextureManager* s_instance;
    std::map<std::string, Texture*> _cacheMap;

   public:
    static TextureManager* getInstance();
    TextureManager();
    ~TextureManager();
    Texture* get(const std::string& name);
};
