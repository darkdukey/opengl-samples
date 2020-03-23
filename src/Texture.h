#pragma once

#include <string>
#include "common.h"

class Texture {
   public:
    Texture(const std::string& path);
    ~Texture();
    void enable(int order = GL_TEXTURE0);

   private:
    uint load(const std::string& path);

   private:
    uint _textureID;
    int _width;
    int _height;
    int _format;
    std::string _path;
};
