#ifndef CONVOLVING_AUTOMATON_CANVAS_H_
#define CONVOLVING_AUTOMATON_CANVAS_H_

#include "FrameBuffer.h"
#include "gl_includes.h"
#include "Shader.h"
#include "Vectors.h"

namespace ca {

class Canvas {
  public:
    Canvas(FrameBuffer* render_target);

    void PaintPoints(const Vec2<float>* points, int count);

  private:
    /**
     * Get paint shader, load if not already loaded.
     */
    static Shader* GetPaintShader();
    
    /**
     *
     */
    static GLuint GetDefaultTexture();
    
    FrameBuffer* background_;
    FrameBuffer* render_target_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_CANVAS_H_