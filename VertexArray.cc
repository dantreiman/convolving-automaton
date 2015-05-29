#include "VertexArray.h"

#include "log.h"
#include "Quad.h"

namespace ca {

VertexArray* VertexArray::Default() {
    static VertexArray* defaultArray = NULL;
    if (defaultArray == NULL) {
        // Create a VAO
        GLuint vao;
        Quad quad = Quad(-1, -1, 2, 2);
        glGenVertexArrays(1, &vao);
        CHECK_GL_ERROR("glGenVertexArrays");
        glBindVertexArray(vao);
        CHECK_GL_ERROR("glBindVertexArray");
        GLuint posBufferName;
        glGenBuffers(1, &posBufferName);
        CHECK_GL_ERROR("glGenBuffers");
        glBindBuffer(GL_ARRAY_BUFFER, posBufferName);
        CHECK_GL_ERROR("glBindBuffer");
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), &quad.vertices[0], GL_STATIC_DRAW);
        CHECK_GL_ERROR("glBufferData");
        glEnableVertexAttribArray(POS_ATTRIB_LOCATION);
        CHECK_GL_ERROR("glEnableVertexAttribArray");
        glVertexAttribIPointer(POS_ATTRIB_LOCATION,
                               2,
                               GL_INT,
                               0,
                               BUFFER_OFFSET(0));
        CHECK_GL_ERROR("glVertexAttribIPointer");
		defaultArray = new VertexArray(vao, 4);
    }
    return defaultArray;
}

VertexArray::VertexArray(GLuint vao, GLsizei count) :
    vao_(vao),
    count_(count) {}

VertexArray::~VertexArray() {
    // TODO: Delete vertex array
}

void VertexArray::Bind() const {
    glBindVertexArray(vao_);
    CHECK_GL_ERROR("glBindVertexArray");
}

void VertexArray::Draw() const {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CHECK_GL_ERROR("glDrawArrays");
}

}  // namespace ca