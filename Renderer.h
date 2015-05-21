#ifndef CONVOLVING_AUTOMATON_RENDERER_H_
#define CONVOLVING_AUTOMATON_RENDERER_H_

#include <random>
#include "FrameBuffer.h"
#include "gl_includes.h"
#include "Shader.h"
#include "utils.h"

namespace ca {

struct Vertex {
    Vertex() : x(0), y(0) {}
    Vertex(int x, int y) : x(x), y(y) {}
    GLint x;
    GLint y;
};


class Renderer {
 public:
  Renderer(const Size& rtt_size, GLuint default_framebuffer);
  
  /**
   * Configure gl state.
   */
  void Init();

  void RandomRects(GLFWwindow* window, float length, int iter);

  void DrawState(GLFWwindow* window, const FrameBuffer* state);

  void Resize(int width, int height);

 private:
	float aspect_ratio_; // The aspect ratio of the render output device
	Size rtt_size_;
	GLuint default_framebuffer_;
	Vertex vertices_[4];
	std::default_random_engine generator_;
	std::unique_ptr<Shader> draw_shader_;
	GLuint vao_;
	// uniform locations
	GLint uniform_stateTexture_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_RENDERER_H_