#include "Renderer.h"

#include "gl_includes.h"
#include "log.h"
#include "VertexArray.h"
#include "minimal_vertex_shader.h"
#include "draw_2d_hue_shader.h"
#include "draw_2d_gradient_shader.h"

namespace ca {

Renderer::Renderer(const Size& rtt_size, GLuint default_framebuffer) :
    rtt_size_(rtt_size),
    default_framebuffer_(default_framebuffer) {}

void Renderer::Init() {
    fprintf(LOGFILE, "Configuring Renderer\n");
    fprintf(LOGFILE, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    fprintf(LOGFILE, "OpenGL Shader Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    // Load default shader
    Shader * hue_shader = new Shader(minimal_vertex_shader_src, draw2d_hue_frag_src);
    hue_shader->Init(ShaderAttributes());
    hue_shader_.reset(hue_shader);
    hue_uniforms_.state_texture_location = hue_shader_->UniformLocation("stateTexture");
    Shader * gradient_shader = new Shader(minimal_vertex_shader_src, draw2d_gradient_frag_src);
    gradient_shader->Init(ShaderAttributes());
    gradient_shader_.reset(gradient_shader);
    gradient_uniforms_.background_color_location = gradient_shader_->UniformLocation("backgroundColor");
    gradient_uniforms_.color1_location = gradient_shader_->UniformLocation("color1");
    gradient_uniforms_.color2_location = gradient_shader_->UniformLocation("color2");
    gradient_uniforms_.color3_location = gradient_shader_->UniformLocation("color3");
    gradient_uniforms_.color4_location = gradient_shader_->UniformLocation("color4");
    gradient_uniforms_.state_texture_location = gradient_shader_->UniformLocation("stateTexture");
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

    glUseProgram(hue_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    glBindTexture (GL_TEXTURE_2D, state->texture());
    CHECK_GL_ERROR("glBindTexture");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    VertexArray::Default()->Bind();
    VertexArray::Default()->Draw();
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glUseProgram(0);
}

const Size& Renderer::rtt_size() const {
    return rtt_size_;
}

} // namespace ca