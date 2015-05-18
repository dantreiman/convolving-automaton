#include "Engine.h"

#include <cmath>
#include <iostream>
#include <cstdlib>
#include "log.h"

using namespace std::placeholders;

namespace ca {

Engine::Engine(const Size& world_size) : window_(NULL),
                                         monitor_(NULL),
                                         simulation_(world_size),
                                         renderer_(world_size) {
}

void Engine::Init() {
    
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    int width = 2880, height = 1800;
    monitor_ = glfwGetPrimaryMonitor();
    if (monitor_) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor_);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        width  = mode->width;
        height = mode->height;
    }
    window_ = glfwCreateWindow(width, height, "ConvolvingAutomaton", monitor_, NULL);
    if (!window_) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    if (monitor_) {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    glfwSetWindowSizeCallback(window_, [] (GLFWwindow* window, int width, int height) {
        // TODO: figure out how to bind callback properly
        // renderer_.Resize(width, height);
        glViewport(0, 0, width, height);
    });
    glfwSetKeyCallback(window_, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
                case GLFW_KEY_ESCAPE:
                case GLFW_KEY_Q:
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    break;
                default:
                    break;
            }
        }
    });
    
    renderer_.Init();
    // Set initial aspect ratio
    glfwGetWindowSize(window_, &width, &height);
    renderer_.Resize(width, height);

    // Set up simulation
    simulation_.Init();
}

void Engine::RunLoop() {
    srand ((unsigned)glfwGetTime());

    while (!glfwWindowShouldClose(window_)) {
		glBindTexture (GL_TEXTURE_2D, simulation_.kernel_tex());
		CHECK_GL_ERROR("glBindTexture");
        renderer_.DrawScene(window_, glfwGetTime());
		CHECK_GL_ERROR("DrawScene");
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    // thrd_join(physics_thread, NULL);

    glfwDestroyWindow(window_);
    glfwTerminate();
}

} // namespace ca