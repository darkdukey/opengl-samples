#include <glad/glad.h>
//Don't reorg
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.h"
#include "Cube.h"
#include "Debug.h"
#include "FileUtil.h"
#include "Model.h"
#include "Scene.h"
#include "Sprite.h"
#include "common.h"

using namespace std;
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

    auto root = Node::create();
    sc->addChild(root);

    // Create light
    auto directLight = Light::create("sun", Directional);
    directLight->position(0, 20, 10);
    directLight->setColor(0.4, 0, 0);
    sc->addLight(directLight);

    // auto mod = Model::create("models/room/model.gltf");
    auto mod = Model::create("models/nanosuit/scene.gltf");
    mod->load();
    sc->addChild(mod);

    // auto sp1 = Sprite::create("textures/awesomeface.png");
    // sp1->x(0.5f);
    // sc->addChild(sp1);
    // auto sp2 = Sprite::create("textures/wall.jpg");
    // sp2->x(-0.5f);
    // sc->addChild(sp2);

    auto cb1 = Cube::create("textures/wall.jpg");
    root->addChild(cb1);

    auto cam = Camera::create(800, 600);
    cam->position(0, 20, 10);
    cam->lookat(0, 10, 0);
    sc->addCamera(cam);

    //TODO: move this to renderer
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sc->draw();
        sc->update();
        root->rotByY(0.1f);
        mod->rotByY(-0.1f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
