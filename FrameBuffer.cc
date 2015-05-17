#include "FrameBuffer.h"

namespace ca {

FrameBuffer::FrameBuffer(GLuint texture, GLuint framebuffer) :
             texture_(texture),
             framebuffer_(framebuffer) {}

}  // namespace ca