#include "FrameBuffer.h"

namespace ca {

FrameBuffer::FrameBuffer(GLuint texture, GLuint framebuffer) :
             texture_(texture),
             framebuffer_(framebuffer) {}

GLuint FrameBuffer::texture() const {
    return texture_;
}

GLuint FrameBuffer::framebuffer() const {
    return framebuffer_;
}

}  // namespace ca