#include "gtest/gtest.h"
// GTest header

#include "Director.h"
#include "Node.h"
#include "Scene.h"

using namespace std;

class CoreTest : public ::testing::Test {
   protected:
    CoreTest() {
    }

    ~CoreTest() override {
    }
};

TEST_F(CoreTest, SceneSwitch) {
    auto sc1 = Scene::create();
    auto sc2 = Scene::create();

    //Empty Scene
    auto curr = G::ins().curr();
    EXPECT_EQ(curr, nullptr);

    //Push/Pop Scene
    G::ins().replace(sc1);
    curr = G::ins().curr();
    EXPECT_EQ(curr, sc1);

    G::ins().replace(sc2);
    curr = G::ins().curr();
    EXPECT_EQ(curr, sc2);

    G::ins().pop();
    curr = G::ins().curr();
    EXPECT_EQ(curr, nullptr);
}

TEST_F(CoreTest, AddRemoveNode) {
    auto n1 = Node::create();
    auto n2 = Node::create();

    auto sc1 = Scene::create();
    sc1->addChild(n1);
    sc1->addChild(n2);
    EXPECT_NE(n1->getParent(), nullptr);
    EXPECT_NE(n2->getParent(), nullptr);
    sc1->removeChild(n1);
    EXPECT_EQ(n1->getParent(), nullptr);
    EXPECT_NE(n2->getParent(), nullptr);
}

TEST_F(CoreTest, SceneUpdate) {
    auto n1 = Node::create();
    auto sc1 = Scene::create();
    sc1->onUpdate([n1]() {
        n1->sx(1.0f);
    });
    sc1->addChild(n1);
    G::ins().replace(sc1);

    G::ins().curr()->update();

    EXPECT_EQ(n1->x(), 1.0f);
}
