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

// Draws shapes on a texture's image, writing the blended output into
// another texture.
class Canvas {
  public:
    // Initialize the canvas.
    Canvas(FrameBuffer* render_target, const Size& size);

    // Paint anti-aliased circles at the positions specified by points.
    void PaintCircles(const Vec2<float>* points, int count, float radius);

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