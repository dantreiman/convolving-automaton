#include "FrameBufferCache.h"


namespace ca {

 static FrameBufferCache* FrameBufferCache::sharedCache() {
    static FrameBufferCache* shared_instance = NULL;
    if (!shared_instance) {
        shared_instance = new FrameBufferCache(Size(512, 512), 4);
    }
    return shared_instance;
}


FrameBufferCache::FrameBufferCache(const Size& rtt_size, int count) : rtt_size_(rtt_size) {
    GenerateBuffers(count);
}


FrameBufferCache::~FrameBufferCache() {
    for ( auto b : buffers_ ) {
        delete b;
    }
    buffers_.clear();
}

FrameBuffer * FrameBufferCache::ReserveBuffer() {
    if (buffers_.length() == 0) {
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
    
}

}  // namespace ca