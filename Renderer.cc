#include "Renderer.h"

#include "gl_includes.h"
#include "log.h"

namespace ca {

Renderer::Renderer(const Size& rtt_size, GLuint default_framebuffer) :
	aspect_ratio_(1),
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

void Renderer::RandomRects(GLFWwindow* window, float length, int iter) {
    // glEnableClientState(GL_VERTEX_ARRAY);
    //     std::uniform_int_distribution<int> x_dist(0, rtt_size_.w);
    //     std::uniform_int_distribution<int> y_dist(0, rtt_size_.h);
    //     std::uniform_int_distribution<int> r_dist(length * .5, length * 1.5);
    //     
    //     // glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    //     for (int i = 0; i < iter; i++) {
    //         float x = x_dist(generator_);
    //         float y = y_dist(generator_);
    //         float w = r_dist(generator_);
    //         float h = r_dist(generator_);
    //  Quad quad(x, y, w, h);
    //  glVertexPointer(2, GL_INT, 0, quad.vertices);
    //  glDrawArrays(GL_TRIANGLE_STRIP, 0, 2);
    //     }
    // glDisableClientState(GL_VERTEX_ARRAY);
}

void Renderer::DrawState(GLFWwindow* window, const FrameBuffer* state) {
	glBindFramebuffer(GL_FRAMEBUFFER, default_framebuffer_);
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

void Renderer::Resize(int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "glViewport(0, 0," << width << ", " << height << ")" << std::endl;
    aspect_ratio_ = height ? width / (float)height : 1.f;
}

} // namespace ca