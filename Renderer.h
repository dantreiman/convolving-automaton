#ifndef CONVOLVING_AUTOMATON_RENDERER_H_
#define CONVOLVING_AUTOMATON_RENDERER_H_

#include <GLFW/glfw3.h>
#include <random>
#include "utils.h"

namespace ca {

class Renderer {
 public:
  Renderer(const Size& rtt_size);
  
  void RandomRects(GLFWwindow* window, float length, int iter);

  void DrawScene(GLFWwindow* window, double t);

  void Resize(int width, int height);

 private:
	float aspect_ratio_; // The aspect ratio of the render output device
	Size rtt_size_;
	std::default_random_engine generator_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_RENDERER_H_