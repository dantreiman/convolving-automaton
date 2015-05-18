#ifndef CONVOLVING_AUTOMATON_FRAMEBUFFERCACHE_H_
#define CONVOLVING_AUTOMATON_FRAMEBUFFERCACHE_H_
//
// A buffer pool which acts like an LRU cache.
// Creates new framebuffers as-needed and facilitates re-use.
// Thread-safe singleton.
//

#include <vector>
#include "FrameBuffer.h"
#include "gl_includes.h"
#include "utils.h"

namespace ca {

class FrameBufferCache {
 public:

  /**
   * Shared buffer cache.
   */
    static FrameBufferCache* sharedCache(const Size& rtt_size);

  /**
   * Initialize the cache using the specified size and count;
   */
  FrameBufferCache(const Size& rtt_size, int count);
  ~FrameBufferCache();
  
  FrameBuffer * ReserveBuffer();
  void RecycleBuffer(FrameBuffer * buffer);

 private:
    void GenerateBuffers(int count);
    
    std::vector<FrameBuffer *> buffers_;
    Size rtt_size_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_FRAMEBUFFERCACHE_H_