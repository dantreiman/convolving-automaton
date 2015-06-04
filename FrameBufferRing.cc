#include "FrameBufferRing.h"

namespace ca {

FrameBufferRing::FrameBufferRing() {}

FrameBufferRing::~FrameBufferRing() {
    // TODO: delete any buffers still owned by the ring
}

FrameBuffer * FrameBufferRing::read_buffer() const {
    return ring_.front();
}

FrameBuffer * FrameBufferRing::write_buffer() const {
    auto it = ring_.begin();
    std::advance(it, 1);
    return *it;
}

void FrameBufferRing::Rotate() {
    FrameBuffer * new_idle = ring_.front();
    ring_.pop_front();
    ring_.push_back(new_idle);
}

void FrameBufferRing::Add(FrameBuffer * buffer) {
    ring_.push_back(buffer);
}

FrameBuffer * FrameBufferRing::RemoveIdle() {
    FrameBuffer * idle = ring_.back();
    ring_.pop_back();
    return idle;
}

}  // namespace ca