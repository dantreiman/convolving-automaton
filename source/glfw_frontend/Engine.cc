#include "Engine.h"

#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Canvas.h"
#include "FrameBuffer.h"
#include "log.h"

using namespace std::placeholders;

namespace ca {

Engine::Engine(const Size& world_size, bool fullscreen) :
    fullscreen_(fullscreen),
    window_(NULL),
    monitor_(NULL),
    simulation_(world_size),
    renderer_(world_size, 0) {
}

void Engine::Init() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    // Use OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const Size& world_size = renderer_.rtt_size();
    int width = world_size.w, height = world_size.h;

    monitor_ = glfwGetPrimaryMonitor();
    if (monitor_) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor_);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        if (fullscreen_) {
            width  = mode->width;
            height = mode->height;
        }
    }
    
    GLFWmonitor* display_to_capture = fullscreen_ ? monitor_ : NULL;
    window_ = glfwCreateWindow(width, height, "ConvolvingAutomaton", display_to_capture, NULL);
    if (!window_) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    if (monitor_ && fullscreen_) {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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
        // Paint to screen if button down
        if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double x, y;
            glfwGetCursorPos(window_, &x, &y);
            // Transform cursor pos to lower-left origin
            int w, h;
            glfwGetWindowSize(window_, &w, &h);
            y = h - y;
            // paint
            FrameBuffer* state = simulation_.RemoveStateBuffer();
            Canvas canvas(state);
            Vec2<float> n(x / w, y / h);  // normalize coordinates to [0,1]
            Vec2<float> touches[2];
            touches[0] = Vec2<float>(n.x * 2 - 1, n.y * 2 - 1);  // scale coordinates to [-1,1]
            touches[1] = Vec2<float>((1.0 - n.x) * 2 - 1, (1.0 - n.y) * 2 - 1);  // scale coordinates to [-1,1]
            canvas.PaintPoints(touches, 2);
            simulation_.InsertStateBuffer(state);
        }
        
        //float t = glfwGetTime();
        // For now, simulation and rendering run in same thread
        // TODO: run simulation async, lock state buffer when its time to draw.
        simulation_.Step();
        FrameBuffer* state = simulation_.LockRenderingBuffer();
        renderer_.DrawState(window_, state);
        simulation_.UnlockRenderingBuffer(state);
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    // thrd_join(physics_thread, NULL);
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Engine::TestPerformance() {
    simulation_.TestPerformance();
    // simulation_.TestFFTPerformance();
    glfwSwapBuffers(window_);
    glfwDestroyWindow(window_);
    glfwTerminate();
}

} // namespace ca