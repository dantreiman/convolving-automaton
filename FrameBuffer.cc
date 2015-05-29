#include "FrameBuffer.h"

#include <sstream>
#include "log.h"

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

void FrameBuffer::BindFrameBuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer());
    CHECK_GL_ERROR("glBindFrameBuffer");
}

std::string FrameBuffer::DebugString() const {
    std::stringstream stream;
    stream << " framebuffer: " << framebuffer() << " texture: " << texture();
    return stream.str();
}

}  // namespace ca