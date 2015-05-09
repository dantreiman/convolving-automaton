#include "Renderer.h"

namespace ca {

Renderer::Renderer() {}

void Renderer::DrawScene(GLFWwindow* window, double t) {
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace ca