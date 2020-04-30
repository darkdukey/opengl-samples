#include "gtest/gtest.h"
// GTest header

#include "Director.h"
#include "Scene.h"

using namespace std;

class CoreTest : public ::testing::Test {
   protected:
    CoreTest() {
    }

    ~CoreTest() override {
    }
};

TEST_F(CoreTest, Director) {
    auto sc1 = Scene::create();
    auto sc2 = Scene::create();

    //Empty Scene
    auto curr = G::ins().curr();
    EXPECT_EQ(curr, nullptr);

    //Push/Pop Scene
    G::ins().push(sc1);
    curr = G::ins().curr();
    EXPECT_EQ(curr, sc1);

    G::ins().swich(sc2);
    curr = G::ins().curr();
    EXPECT_EQ(curr, sc2);

    G::ins().pop();
    curr = G::ins().curr();
    EXPECT_EQ(curr, nullptr);
}
