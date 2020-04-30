#pragma once

#include <memory>
#include <stack>

class Scene;

/**
 * G is holds all the scenes in this tiny universe.
 **/
class G {
   private:
    std::stack<std::shared_ptr<Scene>> _sceneStack;

   private:
    G();
    ~G();

   public:
    static G& ins() {
        static G g{};
        return g;
    }

    std::shared_ptr<Scene> curr();
    void push(std::shared_ptr<Scene> scene);
    void pop();
    void swich(std::shared_ptr<Scene> scene);
};