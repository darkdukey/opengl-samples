#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"

using namespace std;

shared_ptr<Camera> Camera::create(int width, int height) {
    return make_shared<Camera>(width, height);
}

Camera::Camera(int width, int height)
    : _width(width), _height(height) {
    _pos = glm::vec3(0.0f);
    refresh();
}

Camera::~Camera() {
}

void Camera::spos(float x, float y, float z) {
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
    refresh();
}

void Camera::onAddToScene(Scene* scene) {
    scene->addCamera(Node::downcasted_shared_from_this<Camera>());
    Node::onAddToScene(scene);
}

void Camera::onRemoveFromScene(Scene* scene) {
    scene->removeCamera(Node::downcasted_shared_from_this<Camera>());
    Node::onRemoveFromScene(scene);
}

void Camera::lookat(float x, float y, float z) {
    _view = glm::lookAt(_pos, glm::vec3(x, y, z), glm::vec3(0, 1, 0));
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
