#include "Renderer.h"

#include "gl_includes.h"
#include "log.h"
#include "VertexArray.h"

namespace ca {

Renderer::Renderer(const Size& rtt_size, GLuint default_framebuffer) :
    rtt_size_(rtt_size),
    default_framebuffer_(default_framebuffer) {}

void Renderer::Init() {
    fprintf(LOGFILE, "Configuring Renderer\n");
    fprintf(LOGFILE, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    fprintf(LOGFILE, "OpenGL Shader Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    // Load default shader
    Shader * draw_shader = new Shader("minimal", "draw2D_new");
    draw_shader->Init(ShaderAttributes());
    draw_shader_.reset(draw_shader);
    uniform_stateTexture_ = draw_shader_->UniformLocation("stateTexture");
    // Set up default settings
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Renderer::DrawState(GLFWwindow* window, const FrameBuffer* state) {
    Size frame_size;
    glBindFramebuffer(GL_FRAMEBUFFER, default_framebuffer_);
    // Resize renderer, since simulation RTT changes viewport
    glfwGetFramebufferSize(window, &frame_size.w, &frame_size.h);
    // std::cout << "glViewport(0, 0," << frame_size.w << ", " << frame_size.h << ")" << std::endl;
    glViewport(0, 0, frame_size.w, frame_size.h);
    
    glClearColor(0.4f, 0.4f, 1.0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    CHECK_GL_ERROR("glClear");

    glUseProgram(draw_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    glBindTexture (GL_TEXTURE_2D, state->texture());
    CHECK_GL_ERROR("glBindTexture");
    VertexArray::Default()->Bind();
    VertexArray::Default()->Draw();
    glUseProgram(0);
}

const Size& Renderer::rtt_size() const {
    return rtt_size_;
}

} // namespace ca