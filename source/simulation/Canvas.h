#ifndef CONVOLVING_AUTOMATON_CANVAS_H_
#define CONVOLVING_AUTOMATON_CANVAS_H_

#include "FrameBuffer.h"
#include "gl_includes.h"
#include "Shader.h"
#include "utils.h"
#include "Vectors.h"
#include "VertexArray.h"

#define MAX_POINTS 12

namespace ca {

class Canvas {
  public:
    Canvas(FrameBuffer* render_target, const Size& size);

    void PaintPoints(const Vec2<float>* points, int count, float radius);

  private:
    /**
     * Get paint shader, load if not already loaded.
     */
    static Shader* GetPaintShader();
    
    /**
     * Get the default brush texture.
     */
    static GLuint GetDefaultTexture();
    
    /**
     * Get shared reusable vertex array.
     */
    static VertexArray* GetVertexArray();

    Size size_;
    FrameBuffer* background_;
    FrameBuffer* render_target_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_CANVAS_H_