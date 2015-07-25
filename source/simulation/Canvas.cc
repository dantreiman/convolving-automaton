#include "Canvas.h"

#include <memory>

#include "Buffer.h"
#include "minimal_vertex_shader.h"
#include "KernelGenerator.h"
#include "paint_shaders.h"
#include "Quad.h"
#include "VertexArray.h"

namespace ca {

Canvas::Canvas(FrameBuffer* render_target) :
    render_target_(render_target) {}

void Canvas::PaintPoints(const Vec2<float>* points, int count) {
    const float r = 40;
    Quad<float>* quads = new Quad<float>[count];
    for (int i = 0; i < count; i++) {
        const Vec2<float>& point = points[i];
        quads[i] = Quad<float>(point.x - r, point.y - r, r*2, r*2);
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    CHECK_GL_ERROR("glGenVertexArrays");
    glBindVertexArray(vao);
    CHECK_GL_ERROR("glBindVertexArray");
    GLuint posBufferName;
    glGenBuffers(1, &posBufferName);
    CHECK_GL_ERROR("glGenBuffers");
    glBindBuffer(GL_ARRAY_BUFFER, posBufferName);
    CHECK_GL_ERROR("glBindBuffer");
    glBufferData(GL_ARRAY_BUFFER, 4 * count * sizeof(Quad<float>::Vertex), &quads[0].vertices[0], GL_STATIC_DRAW);
    CHECK_GL_ERROR("glBufferData");
    glEnableVertexAttribArray(POS_ATTRIB_LOCATION);
    CHECK_GL_ERROR("glEnableVertexAttribArray");
    glVertexAttribIPointer(POS_ATTRIB_LOCATION,
                           2,
                           GL_INT,
                           0,
                           BUFFER_OFFSET(0));
    CHECK_GL_ERROR("glVertexAttribIPointer");
    render_target_->BindFrameBuffer();
    glViewport(0, 0, 512, 512);
    glUseProgram(GetPaintShader()->program());
    CHECK_GL_ERROR("glUseProgram");
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, GetDefaultTexture());
    CHECK_GL_ERROR("glBindTexture");

    // bind uniforms
    VertexArray::Default()->Bind();
    VertexArray::Default()->Draw();
    //std::cout << "glDrawArrays" << std::endl;
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4 * count);
    //CHECK_GL_ERROR("glDrawArrays");
}


Shader* Canvas::GetPaintShader() {
    static Shader* paint_shader = NULL;
    if (paint_shader == NULL) {
        paint_shader = new Shader(minimal_vertex_shader_src, paint_frag_src);
        paint_shader->Init(ShaderAttributes());
    }
    return paint_shader;
}


GLuint Canvas::GetDefaultTexture() {
    GLuint default_texture = 0;
    if (default_texture == 0) {
        const int s = 128;
        Buffer2D<float> buffer(Size(s, s));
        KernelGenerator::MakeCircle(80,
                                    1,
                                    &buffer);
        glGenTextures(1, &default_texture);
        CHECK_GL_ERROR("glGenTextures");
        glBindTexture(GL_TEXTURE_2D, default_texture);
        CHECK_GL_ERROR("glBindTexture");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA /* color components */, s, s, 0, GL_RED, GL_FLOAT, buffer.data());
        CHECK_GL_ERROR("glTexImage2D");
    }
    return default_texture;
}

}  //  namespace ca