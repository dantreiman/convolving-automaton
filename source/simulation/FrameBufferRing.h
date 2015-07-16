#ifndef CONVOLVING_AUTOMATON_FRAMEBUFFERRING_H_
#define CONVOLVING_AUTOMATON_FRAMEBUFFERRING_H_
//
// Manages a rotating ring of buffers.
// ring_.begin() is the write buffer.
// ring_.begin()+1 is the read buffer.
// ring_.end() points to the idle buffer (the buffer which can be removed from the ring).
// Must contain at least two buffers (one for reading, one for writing),
//
// If there are only two buffers, RemoveIdle will return NULL, and
// Rotate is equivalent to swap.
//

#include <list>
#include "FrameBuffer.h"
#include "gl_includes.h"

namespace ca {

class FrameBufferRing {
 public:
  FrameBufferRing();
  ~FrameBufferRing();
  
  FrameBuffer * read_buffer() const;
  FrameBuffer * write_buffer() const;

  void Rotate();
  void Add(FrameBuffer * buffer);
  FrameBuffer * RemoveIdle();

 private:
    std::list<FrameBuffer *> ring_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_FRAMEBUFFERRING_H_