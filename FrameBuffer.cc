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

void FrameBuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer());
    CHECK_GL_ERROR("glBindFrameBuffer");
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture(), 0);
    CHECK_GL_ERROR("glFramebufferTexture2D");
}

std::string FrameBuffer::DebugString() const {
    std::stringstream stream;
    stream << " framebuffer: " << framebuffer() << " texture: " << texture();
    return stream.str();
}

}  // namespace ca