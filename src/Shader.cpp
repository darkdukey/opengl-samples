#include <glad/glad.h>
//User headers
#include <glm/gtc/type_ptr.hpp>
#include "Debug.h"
#include "FileUtil.h"
#include "Shader.h"

using namespace std;
using namespace NT;

Shader::Shader(const string& vertexPath, const string& fragmentPath) {
    int success;
    char infoLog[512];

    // shader
    uint vertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
    uint fragmentShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);

    _shaderID = glCreateProgram();
    glAttachShader(_shaderID, vertexShader);
    glAttachShader(_shaderID, fragmentShader);
    glLinkProgram(_shaderID);
    glGetProgramiv(_shaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderID, 512, NULL, infoLog);
        cout << "ERROR: " << infoLog << endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
}

void Shader::enable() {
    glUseProgram(_shaderID);
}

void Shader::setBool(const string& name, bool value) const {
    glUniform1i(glGetUniformLocation(_shaderID, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value) const {
    glUniform1i(glGetUniformLocation(_shaderID, name.c_str()), value);
}

void Shader::setFloat(const string& name, float value) const {
    glUniform1f(glGetUniformLocation(_shaderID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(_shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

uint Shader::createShader(const string& path, GLuint type) {
    int success;
    char infoLog[512];

    uint shaderID;
    string source;
    if (FileUtil::exists(path)) {
        source = FileUtil::readFile(path);
    }

    shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        log(error) << "ERROR: " << infoLog;
    }
    return shaderID;
}