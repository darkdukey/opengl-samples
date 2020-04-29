#include "Director.h"

#include "Scene.h"

using namespace std;

G* G::s_instance = nullptr;

G* G::ins() {
    if (s_instance == nullptr) {
        s_instance = new G();
    }

    return s_instance;
}

G::G() {
}

G::~G() {
}

shared_ptr<Scene> G::curr() {
    if (!_sceneStack.empty()) {
        return _sceneStack.top();
    }

    return nullptr;
}

void G::push(shared_ptr<Scene> scene) {
    _sceneStack.push(scene);
}

void G::pop() {
    if (!_sceneStack.empty()) {
        _sceneStack.pop();
    }
}

void G::swich(shared_ptr<Scene> scene) {
    if (!_sceneStack.empty()) {
        _sceneStack.pop();
    }
    _sceneStack.push(scene);
}