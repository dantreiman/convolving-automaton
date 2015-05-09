#include "Engine.h"

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

namespace ca {

Engine::Engine() : window_(NULL), monitor_(NULL) {
    render_size_.width = 512;
    render_size_.height = 512;
}

void Engine::Init() {
    
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
	float width = 2880, height = 1800;
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
        glViewport(0, 0, width, height);
        //aspect_ratio = height ? width / (float) height : 1.f;
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
    
    // Set initial aspect ratio
    // glfwGetWindowSize(window, &width, &height);
    // resize_callback(window, width, height);
}

void Engine::RunLoop() {
    srand ((unsigned)glfwGetTime());

    while (!glfwWindowShouldClose(window_)) {
        renderer.DrawScene(window_, glfwGetTime());
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    // thrd_join(physics_thread, NULL);

    glfwDestroyWindow(window_);
    glfwTerminate();
}

} // namespace ca