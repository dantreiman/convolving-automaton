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
    // Load gradient shader
    Shader * draw_gradient_shader = new Shader("minimal", "draw2D_gradient");
    draw_gradient_shader->Init(ShaderAttributes());
    draw_gradient_shader_.reset(draw_gradient_shader);
    uniforms_.background_color_location = draw_gradient_shader_->UniformLocation("backgroundColor");
    uniforms_.color1_location = draw_gradient_shader_->UniformLocation("color1");
    uniforms_.color2_location = draw_gradient_shader_->UniformLocation("color2");
    uniforms_.color3_location = draw_gradient_shader_->UniformLocation("color3");
    uniforms_.color4_location = draw_gradient_shader_->UniformLocation("color4");
    uniforms_.state_texture_location = draw_gradient_shader_->UniformLocation("stateTexture");
    // Set up default settings
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    // Load color scheme
	color_scheme_ = ColorScheme::GetPreset(2);
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

	if (false) {
	    glUseProgram(draw_gradient_shader_->program());
	    CHECK_GL_ERROR("glUseProgram");
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture (GL_TEXTURE_2D, state->texture());
	    CHECK_GL_ERROR("glBindTexture");
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glUniform1i(uniforms_.state_texture_location, 0);
	    glUniform4fv(uniforms_.background_color_location, 1, color_scheme_.background_color);
	    glUniform4fv(uniforms_.color1_location, 1, color_scheme_.color1);
	    glUniform4fv(uniforms_.color2_location, 1, color_scheme_.color2);
	    glUniform4fv(uniforms_.color3_location, 1, color_scheme_.color3);
	    glUniform4fv(uniforms_.color4_location, 1, color_scheme_.color4);
	    VertexArray::Default()->Bind();
	    VertexArray::Default()->Draw();
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else {
		glUseProgram(draw_shader_->program());
	    CHECK_GL_ERROR("glUseProgram");
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture (GL_TEXTURE_2D, state->texture());
	    CHECK_GL_ERROR("glBindTexture");
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glUniform1i(uniform_stateTexture_, 0);
	    VertexArray::Default()->Bind();
	    VertexArray::Default()->Draw();
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
    glUseProgram(0);
}

const Size& Renderer::rtt_size() const {
    return rtt_size_;
}

} // namespace ca