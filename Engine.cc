#include "Engine.h"

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

namespace ca {

Engine::Engine() : window_(NULL), monitor_(NULL) {
    render_size_.width = 512;
    render_size_.height = 512;
}

Engine::~Engine() {}

void Engine::Init() {
    
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    monitor_ = glfwGetPrimaryMonitor();
    if (monitor_) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor_);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    }
    window_ = glfwCreateWindow(render_size_.width, render_size_.height, "ConvolvingAutomaton", monitor_, NULL);
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
    // glfwSetWindowSizeCallback(window, resize_callback);
    // glfwSetKeyCallback(window, key_callback);

    // Set initial aspect ratio
    // glfwGetWindowSize(window, &width, &height);
    // resize_callback(window, width, height);
}

void Engine::RunLoop() {
    srand ((unsigned)glfwGetTime());

    while (!glfwWindowShouldClose(window_)) {
        // draw_scene(window_, glfwGetTime());
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

	// thrd_join(physics_thread, NULL);

    glfwDestroyWindow(window_);
    glfwTerminate();
}

} // namespace ca