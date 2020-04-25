#pragma once

#include <memory>
#include <stack>

class Scene;
class Director {
   private:
    static Director* s_instance;
    std::stack<std::shared_ptr<Scene>> _sceneStack;

   public:
    static Director* getInstance();
    Director();
    ~Director();
    std::shared_ptr<Scene> getCurrScene();
    void pushScene(std::shared_ptr<Scene> scene);
    void popScene();
};