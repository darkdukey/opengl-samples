#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(int width, int height)
    : _width(width), _height(height) {
    _pos = glm::vec3(0.0f);
    refresh();
}

Camera::~Camera() {
}

void Camera::position(float x, float y, float z) {
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
}

void Camera::lookat(float x, float y, float z) {
}

void Camera::viewport(int width, int height) {
}

void Camera::refresh() {
    //TODO: implement scene
    switch (_mode) {
        case Perspective:
            _proj = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);
            break;
        case Orthographic:
            _proj = glm::ortho(0.0f, (float)_width, 0.0f, (float)_height, 0.1f, 100.0f);
            break;
        default:
            _proj = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);
            break;
    }
    _view = glm::translate(glm::mat4(1.0f), _pos);
}
