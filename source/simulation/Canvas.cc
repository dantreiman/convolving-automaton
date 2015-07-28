#include "Canvas.h"

#include <memory>

#include "Buffer.h"
#include "minimal_vertex_shader.h"
#include "KernelGenerator.h"
#include "paint_shaders.h"
#include "Quad.h"


static GLuint pos_buffer;
static GLuint tex_buffer;

namespace ca {

Canvas::Canvas(FrameBuffer* render_target) :
    render_target_(render_target) {}

void Canvas::PaintPoints(const Vec2<float>* points, int count) {
    std::cout << "Point: " << points[0].ToString() << std::endl;
    GetVertexArray(); // ensure vertex array exists
    const float r = .2;
    Quad<float>* quads = new Quad<float>[count];
    
    for (int i = 0; i < count; i++) {
        const Vec2<float>& point = points[i];
        quads[i] = Quad<float>(point.x - r, point.y - r, r*2, r*2);
    }
    GetVertexArray()->Bind();
    glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
    CHECK_GL_ERROR("glBindBuffer");
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * count * sizeof(Vec2<float>), &quads[0]);
    CHECK_GL_ERROR("glBufferSubData");
    delete quads;
    
    render_target_->BindFrameBuffer();
    glViewport(0, 0, 512, 512);
    glUseProgram(GetPaintShader()->program());
    CHECK_GL_ERROR("glUseProgram");
    glUniform1i(GetPaintShader()->UniformLocation("brush"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GetDefaultTexture());
    CHECK_GL_ERROR("glBindTexture");
    GetVertexArray()->SetCount(count * 4);
    glEnableVertexAttribArray(POS_ATTRIB_LOCATION);
    CHECK_GL_ERROR("POS_ATTRIB_LOCATION");
    //glEnableVertexAttribArray(TEX_ATTRIB_LOCATION);
    //CHECK_GL_ERROR("TEX_ATTRIB_LOCATION");
    // VertexArray::Default()->Bind();
    // VertexArray::Default()->Draw();
    GetVertexArray()->Bind();
    GetVertexArray()->Draw();
    //glDisableVertexAttribArray(TEX_ATTRIB_LOCATION);
}


Shader* Canvas::GetPaintShader() {
    static Shader* paint_shader = NULL;
    if (paint_shader == NULL) {
        paint_shader = new Shader(paint_vert_src, paint_frag_src);
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


VertexArray* Canvas::GetVertexArray() {
    static VertexArray* vertex_array = NULL;
    if (vertex_array == NULL) {
        const float r = .2;
        Quad<float>* quads = new Quad<float>[MAX_POINTS];
        Vec2<float>* texcoords = new Vec2<float>[MAX_POINTS * 4];

        for (int i = 0; i < MAX_POINTS; i++) {
            // init quads to test values
            quads[i] = Quad<float>(.5, .5, .2, .2);
            // init texcoords to correct values
            const int vi = i * 4;
            texcoords[vi] = Vec2<float>(0,0);
            texcoords[vi+1] = Vec2<float>(1,0);
            texcoords[vi+2] = Vec2<float>(1,1);
            texcoords[vi+3] = Vec2<float>(0,1);
        }

        GLuint vao;
        glGenVertexArrays(1, &vao);
        CHECK_GL_ERROR("glGenVertexArrays");
        glBindVertexArray(vao);
        CHECK_GL_ERROR("glBindVertexArray");
        // POSITION BUFFER
        glGenBuffers(1, &pos_buffer);
        CHECK_GL_ERROR("glGenBuffers");
        glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
        CHECK_GL_ERROR("glBindBuffer");
        glBufferData(GL_ARRAY_BUFFER, 4 * MAX_POINTS * sizeof(Quad<float>::Vertex), &quads[0].vertices[0], GL_DYNAMIC_DRAW);
        CHECK_GL_ERROR("glBufferData");
        glEnableVertexAttribArray(POS_ATTRIB_LOCATION);
        CHECK_GL_ERROR("glEnableVertexAttribArray");
        glVertexAttribPointer(POS_ATTRIB_LOCATION, 2, GL_FLOAT, true, 0, BUFFER_OFFSET(0));
        CHECK_GL_ERROR("glVertexAttribPointer");
        // TEXCOORD BUFFER
        glGenBuffers(1, &tex_buffer);
        CHECK_GL_ERROR("glGenBuffers");
        glBindBuffer(GL_ARRAY_BUFFER, tex_buffer);
        CHECK_GL_ERROR("glBindBuffer");
        glBufferData(GL_ARRAY_BUFFER, 4 * MAX_POINTS * sizeof(Vec2<float>), &texcoords[0], GL_DYNAMIC_DRAW);
        CHECK_GL_ERROR("glBufferData");
        glEnableVertexAttribArray(TEX_ATTRIB_LOCATION);
        CHECK_GL_ERROR("glEnableVertexAttribArray");
        glVertexAttribPointer(TEX_ATTRIB_LOCATION, 2, GL_FLOAT, true, 0, BUFFER_OFFSET(0));
        CHECK_GL_ERROR("glVertexAttribPointer");

        vertex_array = new VertexArray(vao, 4 * MAX_POINTS);
        delete quads;
        delete texcoords;
    }
    return vertex_array;
}


}  //  namespace ca