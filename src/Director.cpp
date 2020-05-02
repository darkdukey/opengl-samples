#include "Director.h"

#include "Renderer.h"
#include "Scene.h"

using namespace std;

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
    if (_sceneStack.empty() || _sceneStack.top() != scene) {
        _sceneStack.push(scene);
        scene->onEnter();
    }
}

void G::pop() {
    if (!_sceneStack.empty()) {
        _sceneStack.top()->onExit();
        Renderer::ins().reset();
        _sceneStack.pop();
    }
}

void G::replace(shared_ptr<Scene> scene) {
    if (curr() != scene) {
        pop();
        push(scene);
    }
}