#include "Director.h"

using namespace std;

Director* Director::s_instance = nullptr;

Director* Director::getInstance() {
    if (s_instance != nullptr) {
        s_instance = new Director();
    }

    return s_instance;
}

Director::Director() {
}

Director::~Director() {
}

shared_ptr<Scene> Director::getCurrScene() {
}

void Director::pushScene(std::shared_ptr<Scene> scene) {
}

void Director::popScene() {
}