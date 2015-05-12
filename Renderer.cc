#include "Renderer.h"

#include "log.h"

namespace ca {

Renderer::Renderer(const Size& rtt_size) : aspect_ratio_(1),
                                           rtt_size_(rtt_size) {}

void Renderer::Init() {
	glDisable(GL_DEPTH_TEST);
	glEnable (GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
}

void Renderer::RandomRects(GLFWwindow* window, float length, int iter) {
    std::uniform_int_distribution<int> x_dist(0, rtt_size_.w);
    std::uniform_int_distribution<int> y_dist(0, rtt_size_.h);
    std::uniform_int_distribution<int> r_dist(length * .5, length * 1.5);
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < iter; i++) {
        float x = x_dist(generator_);
        float y = y_dist(generator_);
        float w = r_dist(generator_);
        float h = r_dist(generator_);
        glVertex2f(x - w, y - w);
        glVertex2f(x + w, y - w);
        glVertex2f(x + w, y + w);
        glVertex2f(x - w, y + w);
    }
    glEnd();
}

void Renderer::DrawScene(GLFWwindow* window, double t) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, rtt_size_.w, 0, rtt_size_.h, -1, 1);
    
    // Setup camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
	glTexCoord2i(0,0); glVertex2i(0, 0);
    glTexCoord2i(1, 0); glVertex2i(rtt_size_.w, 0);
    glTexCoord2i(1, 1); glVertex2i(rtt_size_.w, rtt_size_.h);
    glTexCoord2i(0, 1); glVertex2i(0, rtt_size_.h);
    glEnd();
    //RandomRects(window, 20, 100);
}

void Renderer::Resize(int width, int height) {
    glViewport(0, 0, width, height);    
    aspect_ratio_ = height ? width / (float)height : 1.f;
}

} // namespace ca