#pragma once

#include <memory>
#include <stack>

class Scene;

/**
 * G is holds all the scenes in this tiny universe.
 **/
class G {
   private:
    static G* s_instance;
    std::stack<std::shared_ptr<Scene>> _sceneStack;

   public:
    static G* ins();
    G();
    ~G();

    std::shared_ptr<Scene> curr();
    void push(std::shared_ptr<Scene> scene);
    void pop();
    void swich(std::shared_ptr<Scene> scene);
};