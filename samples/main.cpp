#include <glad/glad.h>
//Don't reorg
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.h"
#include "Cube.h"
#include "Debug.h"
#include "FileUtil.h"
#include "LitCube.h"
#include "Model.h"
#include "Scene.h"
#include "Sprite.h"
#include "common.h"

using namespace std;
using namespace glm;
using namespace NT;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char const* argv[]) {
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto sc = Scene::create();

    // Create light
    auto directLight = Light::create("sun", Directional);
    directLight->spos(0, -2, -4);
    directLight->samb({0.05f, 0.05f, 0.05f});
    directLight->sdiff({0.4f, 0.4f, 0.4f});
    directLight->sspec({0.5f, 0.5f, 0.5f});
    sc->addChild(directLight);

    //Rotating point light
    auto light_root = Node::create();
    light_root->spos(0, 12, 0);

    auto point_light = Light::create("point", Point);
    point_light->spos(0, 0, 5);
    point_light->samb({0.05f, 0.05f, 0.05f});
    point_light->sdiff({0.8f, 0.8f, 0.8f});
    point_light->sspec({1.0f, 1.0f, 1.0f});
    point_light->enableDebugShape();
    light_root->addChild(point_light);
    sc->addChild(light_root);

    // auto mod = Model::create("models/room/model.gltf");
    // auto mod = Model::create("models/nanosuit/scene.gltf");
    // mod->load();
    // sc->addChild(mod);

    Material mat1({1.0f, 0.5f, 0.31f}, {1.0f, 0.5f, 0.31f}, {0.5f, 0.5f, 0.5f}, 32.0f);
    auto cb1 = LitCube::create("material");
    cb1->spos(0, 12, 0);
    cb1->sscale(4, 4, 4);
    cb1->setMaterial(mat1);
    sc->addChild(cb1);

    // Material mat2("textures/container2.png", "textures/container2_specular.png", 32.0f);
    // auto cb2 = LitCube::create("lit");
    // cb2->spos(0, 12, 0);
    // cb2->sscale(4, 4, 4);
    // cb2->setMaterial(mat2);
    // sc->addChild(cb2);

    // auto sp1 = Sprite::create("textures/awesomeface.png");
    // sp1->x(0.5f);
    // sc->addChild(sp1);
    // auto sp2 = Sprite::create("textures/wall.jpg");
    // sp2->x(-0.5f);
    // sc->addChild(sp2);

    auto cam = Camera::create(800, 600);
    cam->spos(0, 15, 10);
    cam->lookat(0, 12, 0);
    sc->addChild(cam);

    //TODO: move this to renderer
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sc->draw();
        sc->update();
        // mod->rotByY(-0.1f);
        light_root->srby(0.5f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
