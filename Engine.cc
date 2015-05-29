#include "Engine.h"

#include <cmath>
#include <iostream>
#include <cstdlib>
#include "FrameBuffer.h"
#include "log.h"

using namespace std::placeholders;

namespace ca {

Engine::Engine(const Size& world_size) : window_(NULL),
                                         monitor_(NULL),
                                         simulation_(world_size),
                                         renderer_(world_size, 0) {
}

void Engine::Init() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    // Use OpenGL version 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    // Set up simulation after renderer, simulation requires GL setup
    simulation_.Init();
}

void Engine::RunLoop() {
    srand ((unsigned)glfwGetTime());

    while (!glfwWindowShouldClose(window_)) {
        //float t = glfwGetTime();
        // For now, simulation and rendering run in same thread
        // TODO: run simulation async, lock state buffer when its time to draw.
        simulation_.Step();
        FrameBuffer* state = simulation_.GetStateBuffer();
        renderer_.DrawState(window_, state);
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    // thrd_join(physics_thread, NULL);

    glfwDestroyWindow(window_);
    glfwTerminate();
}

} // namespace ca