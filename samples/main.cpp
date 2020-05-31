#include <glad/glad.h>
//Don't reorg
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.h"
#include "Cube.h"
#include "Debug.h"
#include "Director.h"
#include "FileUtil.h"
#include "LitCube.h"
#include "Model.h"
#include "Scene.h"
#include "Sprite.h"
#include "common.h"

using namespace std;
using namespace NT;

vector<shared_ptr<Scene>> scenes;
int curr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void onKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        //prev scene
        curr--;
        curr = max(curr, 0);
        G::ins().replace(scenes[curr]);
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        //next scene
        curr++;
        curr = min(curr, (int)(scenes.size() - 1));
        G::ins().replace(scenes[curr]);
    }
}

void createSpotScene() {
    auto sc = Scene::create();
    scenes.push_back(sc);

    auto cam = Camera::create(800, 600);
    cam->spos(0, 15, 10);
    cam->lookat(0, 12, 0);
    sc->addChild(cam);

    Material mat2("textures/container2.png", "textures/container2_specular.png", 32.0f);
    auto cb2 = LitCube::create("lit");
    cb2->spos(0, 12, 0);
    cb2->sscale(4, 4, 4);
    cb2->setMaterial(mat2);
    sc->addChild(cb2);

    auto spot_light1 = Light::create("spot1", Spot);
    spot_light1->spos(0, 12, 7);
    spot_light1->samb({0.05f, 0.05f, 0.05f});
    spot_light1->sdiff({0.8f, 0.8f, 0.8f});
    spot_light1->sspec({1.0f, 1.0f, 1.0f});
    spot_light1->enableDebugShape();
    sc->addChild(spot_light1);

    sc->onUpdate([spot_light1]() {
        // spot_light1->srby(0.5f);
    });
}

void createSpriteScene() {
    auto sc = Scene::create();
    scenes.push_back(sc);

    auto cam = Camera::create(800, 600);
    cam->spos(0, 0, 5);
    cam->lookat(0, 0, 0);
    sc->addChild(cam);

    auto sp1 = Sprite::create("textures/awesomeface.png");
    sp1->sx(0.5f);
    sc->addChild(sp1);
    auto sp2 = Sprite::create("textures/wall.jpg");
    sp2->sx(-0.5f);
    sc->addChild(sp2);
}

void createModelScene() {
    auto sc = Scene::create();
    scenes.push_back(sc);

    auto cam = Camera::create(800, 600);
    cam->spos(0, 15, 10);
    cam->lookat(0, 12, 0);
    sc->addChild(cam);

    auto directLight = Light::create("sun", Directional);
    directLight->spos(0, -2, -4);
    directLight->samb({0.05f, 0.05f, 0.05f});
    directLight->sdiff({0.4f, 0.4f, 0.4f});
    directLight->sspec({0.5f, 0.5f, 0.5f});
    sc->addChild(directLight);

    // auto mod = Model::create("models/room/model.gltf");
    auto mod = Model::create("models/nanosuit/scene.gltf");
    mod->load();
    sc->addChild(mod);
}

void createSolidScene() {
    auto sc = Scene::create();
    scenes.push_back(sc);

    auto cam = Camera::create(800, 600);
    cam->spos(0, 15, 10);
    cam->lookat(0, 12, 0);
    sc->addChild(cam);

    Material mat1({1.0f, 0.5f, 0.31f}, {1.0f, 0.5f, 0.31f}, {0.5f, 0.5f, 0.5f}, 32.0f);
    auto cb1 = LitCube::create("material");
    cb1->spos(0, 12, 0);
    cb1->sscale(4, 4, 4);
    cb1->setMaterial(mat1);
    sc->addChild(cb1);

    auto directLight = Light::create("sun", Directional);
    directLight->spos(0, -2, -4);
    directLight->samb({0.05f, 0.05f, 0.05f});
    directLight->sdiff({0.4f, 0.4f, 0.4f});
    directLight->sspec({0.5f, 0.5f, 0.5f});
    sc->addChild(directLight);

    auto light_root = Node::create();
    light_root->spos(0, 12, 0);
    sc->addChild(light_root);

    auto point_light1 = Light::create("point1", Point);
    point_light1->spos(0, 0, 5);
    point_light1->samb({0.05f, 0.05f, 0.05f});
    point_light1->sdiff({0.8f, 0.8f, 0.8f});
    point_light1->sspec({1.0f, 1.0f, 1.0f});
    point_light1->enableDebugShape();
    light_root->addChild(point_light1);

    auto point_light2 = Light::create("point2", Point);
    point_light2->spos(0, 0, -5);
    point_light2->samb({0.05f, 0.05f, 0.05f});
    point_light2->sdiff({0.8f, 0.2f, 0.2f});
    point_light2->sspec({1.0f, 0.25f, 0.25f});
    point_light2->enableDebugShape();
    light_root->addChild(point_light2);

    auto point_light3 = Light::create("point3", Point);
    point_light3->spos(5, 0, 0);
    point_light3->samb({0.05f, 0.05f, 0.05f});
    point_light3->sdiff({0.2f, 0.8f, 0.2f});
    point_light3->sspec({0.25f, 1.0f, 0.25f});
    point_light3->enableDebugShape();
    light_root->addChild(point_light3);

    auto point_light4 = Light::create("point4", Point);
    point_light4->spos(-5, 0, 0);
    point_light4->samb({0.05f, 0.05f, 0.05f});
    point_light4->sdiff({0.2f, 0.2f, 0.8f});
    point_light4->sspec({0.25f, 0.25f, 1.0f});
    point_light4->enableDebugShape();
    light_root->addChild(point_light4);

    sc->onUpdate([light_root]() {
        light_root->srby(0.5f);
    });
}

void createLitScene() {
    auto sc = Scene::create();
    scenes.push_back(sc);

    auto cam = Camera::create(800, 600);
    cam->spos(0, 15, 10);
    cam->lookat(0, 12, 0);
    sc->addChild(cam);

    Material mat2("textures/container2.png", "textures/container2_specular.png", 32.0f);
    auto cb2 = LitCube::create("lit");
    cb2->spos(0, 12, 0);
    cb2->sscale(4, 4, 4);
    cb2->setMaterial(mat2);
    sc->addChild(cb2);

    auto directLight = Light::create("sun", Directional);
    directLight->spos(0, -2, -4);
    directLight->samb({0.05f, 0.05f, 0.05f});
    directLight->sdiff({0.4f, 0.4f, 0.4f});
    directLight->sspec({0.5f, 0.5f, 0.5f});
    sc->addChild(directLight);

    auto light_root = Node::create();
    light_root->spos(0, 12, 0);
    sc->addChild(light_root);

    auto point_light1 = Light::create("point1", Point);
    point_light1->spos(0, 0, 5);
    point_light1->samb({0.05f, 0.05f, 0.05f});
    point_light1->sdiff({0.8f, 0.8f, 0.8f});
    point_light1->sspec({1.0f, 1.0f, 1.0f});
    point_light1->enableDebugShape();
    light_root->addChild(point_light1);

    auto point_light2 = Light::create("point2", Point);
    point_light2->spos(0, 0, -5);
    point_light2->samb({0.05f, 0.05f, 0.05f});
    point_light2->sdiff({0.8f, 0.2f, 0.2f});
    point_light2->sspec({1.0f, 0.25f, 0.25f});
    point_light2->enableDebugShape();
    light_root->addChild(point_light2);

    auto point_light3 = Light::create("point3", Point);
    point_light3->spos(5, 0, 0);
    point_light3->samb({0.05f, 0.05f, 0.05f});
    point_light3->sdiff({0.2f, 0.8f, 0.2f});
    point_light3->sspec({0.25f, 1.0f, 0.25f});
    point_light3->enableDebugShape();
    light_root->addChild(point_light3);

    auto point_light4 = Light::create("point4", Point);
    point_light4->spos(-5, 0, 0);
    point_light4->samb({0.05f, 0.05f, 0.05f});
    point_light4->sdiff({0.2f, 0.2f, 0.8f});
    point_light4->sspec({0.25f, 0.25f, 1.0f});
    point_light4->enableDebugShape();
    light_root->addChild(point_light4);

    sc->onUpdate([light_root]() {
        light_root->srby(0.5f);
    });
}

void createDepthScene() {
    auto sc = Scene::create();
    scenes.push_back(sc);

    //Create camera
    auto cam = Camera::create(800, 600);
    cam->spos(0, 15, 10);
    cam->lookat(0, 12, 0);
    sc->addChild(cam);

    //Ruby cube in the front
    Material mat_ruby({0.1745, 0.01175, 0.01175}, {0.61424, 0.04136, 0.04136}, {0.727811, 0.626959, 0.626959}, 76.8);
    auto cb3 = LitCube::create("material");
    cb3->spos(-0.5, 12, -1);
    cb3->sscale(2, 2, 2);
    cb3->setMaterial(mat_ruby);
    sc->addChild(cb3);

    //Green cube in the middle
    Material mat_rubber({0, 0.05, 0}, {0.4, 0.5, 0.4}, {0.04, 0.7, 0.04}, 10);
    auto cb2 = LitCube::create("material");
    cb2->spos(0.5, 12, -2);
    cb2->sscale(2, 2, 2);
    cb2->setMaterial(mat_rubber);
    sc->addChild(cb2);

    //Orange cube at the back
    Material mat1({1.0f, 0.5f, 0.31f}, {1.0f, 0.5f, 0.31f}, {0.5f, 0.5f, 0.5f}, 32.0f);
    auto cb1 = LitCube::create("material");
    cb1->spos(0, 12, -8);
    cb1->sscale(4, 4, 4);
    cb1->setMaterial(mat1);
    sc->addChild(cb1);

    //Sun light
    auto directLight = Light::create("sun", Directional);
    directLight->spos(1, -1, -4);
    directLight->samb({0.1f, 0.1f, 0.1f});
    directLight->sdiff({0.4f, 0.4f, 0.4f});
    directLight->sspec({0.5f, 0.5f, 0.5f});
    sc->addChild(directLight);
}

int main(int argc, char const* argv[]) {
    curr = 0;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // For Mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Keyboard input
    glfwSetKeyCallback(window, onKeyboard);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //TODO: move this to renderer
    // glEnable(GL_DEPTH_TEST);

    //Create Scenes
    createDepthScene();
    createSpotScene();
    createSpriteScene();
    createSolidScene();
    createLitScene();
    createModelScene();

    G::ins().replace(scenes[curr]);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        G::ins().curr()->draw();
        G::ins().curr()->update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
