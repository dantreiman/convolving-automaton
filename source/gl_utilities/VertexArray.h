#ifndef CONVOLVING_AUTOMATON_VERTEXARRAY_H_
#define CONVOLVING_AUTOMATON_VERTEXARRAY_H_
//
// A wrapper for a VAO. Provides a shared default VAO for all
// render-to-texture operations.
//

#include <vector>
#include "gl_includes.h"

namespace ca {

class VertexArray {
 public:

  /**
   * Shared VAO for render-to-texture.
   */
    static VertexArray* Default();

  /**
   * Initialize using the specified vertex array object.
   */
  VertexArray(GLuint vao, GLsizei count);
  ~VertexArray();
  
  void SetCount(GLsizei count);

  void Bind() const;
  void Draw() const;

 private:
    GLuint vao_;
    GLsizei count_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_VERTEXARRAY_H_