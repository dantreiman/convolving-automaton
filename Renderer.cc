#include "Renderer.h"

#include "gl_includes.h"
#include "log.h"

namespace ca {
namespace {

enum {
    POS_ATTRIB_IDX,
    NORMAL_ATTRIB_IDX,
    TEXCOORD_ATTRIB_IDX
};


struct Vertex {
    Vertex() : x(0), y(0) {}
    Vertex(int x, int y) : x(x), y(y) {}
    GLint x;
    GLint y;
};

struct Quad {
    Quad(const Size& size) {
        vertices[0] = Vertex(size.w, 0);
        vertices[1] = Vertex(size.w, size.h);
        vertices[2] = Vertex(0, 0);
        vertices[3] = Vertex(0, size.h);
    }
    
    Quad(float x, float y, float w, float h) {
        vertices[0] = Vertex(x + w, y);
        vertices[1] = Vertex(x + w, y + h);
        vertices[2] = Vertex(x, y);
        vertices[3] = Vertex(x, y + h);
    }

    Vertex vertices[4];
};

}  // namespace


Renderer::Renderer(const Size& rtt_size) : aspect_ratio_(1),
                                           rtt_size_(rtt_size) {}

void Renderer::Init() {
    fprintf(LOGFILE, "Configuring Renderer\n");
    fprintf(LOGFILE, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    fprintf(LOGFILE, "OpenGL Shader Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    // Load default shader
    Shader * draw_shader = new Shader("draw2D_new");
    draw_shader->Init();
    draw_shader_.reset(draw_shader);
    // Set up default settings
    glDisable(GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
    // Create full screen rendering VBO
    Quad quad = Quad(rtt_size_);
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    GLuint posBufferName;
    glGenBuffers(1, &posBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, posBufferName);
    glBufferData(GL_ARRAY_BUFFER, 4, quad.vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(POS_ATTRIB_IDX);
    // Set up parmeters for position attribute in the VAO including, 
    // size, type, stride, and offset in the currenly bound VAO
    // This also attaches the position VBO to the VAO
    glVertexAttribPointer(POS_ATTRIB_IDX,  // What attibute index will this array feed in the vertex shader (see buildProgram)
                          2,               // How many elements are there per position?
                          GL_UNSIGNED_INT, // What is the type of this data?
                          GL_FALSE,        // Do we want to normalize this data (0-1 range for fixed-point types)
                          0,               // What is the stride (i.e. bytes between positions)?
                          0);              // What is the offset in the VBO to the position data?
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

void Renderer::DrawScene(GLFWwindow* window, double t) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(0, rtt_size_.w, 0, rtt_size_.h, -1, 1);
    // 
    // // Setup camera
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    // glBegin(GL_QUADS);
    // glTexCoord2i(0,0); glVertex2i(0, 0);
    // glTexCoord2i(1, 0); glVertex2i(rtt_size_.w, 0);
    // glTexCoord2i(1, 1); glVertex2i(rtt_size_.w, rtt_size_.h);
    // glTexCoord2i(0, 1); glVertex2i(0, rtt_size_.h);
    // glEnd();
    glUseProgram(draw_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    glBindVertexArray(vao_);
    CHECK_GL_ERROR("glBindVertexArray");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 2);
    CHECK_GL_ERROR("glDrawArrays");
    
    //RandomRects(window, 20, 100);
}

void Renderer::Resize(int width, int height) {
    glViewport(0, 0, width, height);    
    aspect_ratio_ = height ? width / (float)height : 1.f;
}

} // namespace ca