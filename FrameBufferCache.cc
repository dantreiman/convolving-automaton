#include "FrameBufferCache.h"

#include "log.h"

namespace ca {

FrameBufferCache* FrameBufferCache::sharedCache(const Size &rtt_size) {
    static FrameBufferCache* shared_instance = NULL;
    if (!shared_instance) {
        shared_instance = new FrameBufferCache(rtt_size, 4);
    }
    return shared_instance;
}

FrameBufferCache::FrameBufferCache(const Size& rtt_size, int count) : rtt_size_(rtt_size) {
    GenerateBuffers(count);
}

FrameBufferCache::~FrameBufferCache() {
    for (auto b : buffers_) {
        delete b;
    }
    buffers_.clear();
}

FrameBuffer * FrameBufferCache::ReserveBuffer() {
    if (buffers_.size() == 0) {
        GenerateBuffers(1);
    }
    FrameBuffer * result = buffers_.back();
    buffers_.pop_back();
    return result;
}

void FrameBufferCache::RecycleBuffer(FrameBuffer * buffer) {
    buffers_.push_back(buffer);
}

void FrameBufferCache::GenerateBuffers(int count) {
    GLuint textures[count];
    GLuint framebuffers[count];

    glGenTextures(count, &textures[0]);
    CHECK_GL_ERROR("glGenTextures");
    glGenFramebuffers (count, &framebuffers[0]);
    CHECK_GL_ERROR("glGenFramebuffers");
    
    for (int i = 0; i < count; i++) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        CHECK_GL_ERROR("glBindTexture");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rtt_size_.w, rtt_size_.h, 0, GL_RGBA, GL_FLOAT, NULL);
        CHECK_GL_ERROR("glTexImage2D");
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        CHECK_GL_ERROR("glBindFrameBuffer");
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[i], 0);
        CHECK_GL_ERROR("glFramebufferTexture2D");
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(LOGFILE, "FramebufferStatus 0x%x\n", status);
        }
        GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers
        CHECK_GL_ERROR("glDrawBuffers");
        FrameBuffer * framebuffer = new FrameBuffer(textures[i], framebuffers[i]);
        buffers_.push_back(framebuffer);
    }
}

}  // namespace ca