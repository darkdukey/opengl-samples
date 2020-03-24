#include <glad/glad.h>
//User headers
#include "Debug.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "FileUtil.h"
#include "stb_image.h"

using namespace std;
using namespace NT;

Texture::Texture(const string& path) : _path(path) {
    _textureID = load(path);
}

Texture::~Texture() {
}

void Texture::enable(int order) {
    glActiveTexture(order);
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

uint Texture::load(const string& path) {
    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //make sure image is not upside down
    stbi_set_flip_vertically_on_load(true);
    uchar* data = stbi_load(path.c_str(), &_width, &_height, &_format, 0);
    GLenum texFormat = GL_RGB;
    switch (_format) {
        case 3:
            texFormat = GL_RGB;
            break;
        case 4:
            texFormat = GL_RGBA;
            break;
        default:
            texFormat = GL_RGB;
            break;
    }
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, texFormat, _width, _height, 0, texFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOG(error) << "Failed to load texture";
    }
    stbi_image_free(data);

    return _textureID;
}
