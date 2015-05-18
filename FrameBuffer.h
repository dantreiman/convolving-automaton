#ifndef CONVOLVING_AUTOMATON_FRAMEBUFFER_H_
#define CONVOLVING_AUTOMATON_FRAMEBUFFER_H_

#include "gl_includes.h"

namespace ca {

class FrameBuffer {
 public:
	FrameBuffer(GLuint texture, GLuint framebuffer);
	
 private:
	GLuint texture_;
	GLuint framebuffer_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_FRAMEBUFFER_H_