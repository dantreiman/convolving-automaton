#include "Renderer.h"

#include "gl_includes.h"
#include "log.h"

namespace ca {

Renderer::Renderer(const Size& rtt_size, GLuint default_framebuffer) :
    rtt_size_(rtt_size),
	default_framebuffer_(default_framebuffer) {}

void Renderer::Init() {
    fprintf(LOGFILE, "Configuring Renderer\n");
    fprintf(LOGFILE, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    fprintf(LOGFILE, "OpenGL Shader Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 // Load default shader
    Shader * draw_shader = new Shader("draw2D_new");
    draw_shader->Init(ShaderAttributes());
    draw_shader_.reset(draw_shader);
    uniform_stateTexture_ = draw_shader_->UniformLocation("stateTexture");
    // Set up default settings
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    // Create full screen rendering VBO
    Quad quad = Quad(-1, -1, 2, 2);
	// std::cout << quad.ToString();
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    GLuint posBufferName;
    glGenBuffers(1, &posBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, posBufferName);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), &quad.vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POS_ATTRIB_LOCATION);
    // Set up parmeters for position attribute in the VAO including, 
    // size, type, stride, and offset in the currenly bound VAO
    // This also attaches the position VBO to the VAO
    glVertexAttribIPointer(POS_ATTRIB_LOCATION,
                           2,
                           GL_INT,
                           0,
                           BUFFER_OFFSET(0));
    // glVertexAttribPointer(POS_ATTRIB_LOCATION, // What attibute index will this array feed in the vertex shader (see buildProgram)
    //                       2,                   // How many elements are there per position?
    //                       GL_INT,              // What is the type of this data?
    //                       GL_FALSE,            // Do we want to normalize this data (0-1 range for fixed-point types)
    //                       0,                   // What is the stride (i.e. bytes between positions)?
    //                       BUFFER_OFFSET(0));   // What is the offset in the VBO to the position data?
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
    glBindVertexArray(vao_);
    CHECK_GL_ERROR("glBindVertexArray");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CHECK_GL_ERROR("glDrawArrays");
}

} // namespace ca