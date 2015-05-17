#ifndef CONVOLVING_AUTOMATON_FRAMEBUFFERCACHE_H_
#define CONVOLVING_AUTOMATON_FRAMEBUFFERCACHE_H_
//
// A buffer pool which acts like an LRU cache.
// Creates new framebuffers as-needed and facilitates re-use.
// Thread-safe singleton.
//

#include <GLFW/glfw3.h>
#include "utils.h"

namespace ca {

class FrameBufferCache {
 public:

  /**
   * Shared buffer cache.
   */
  static FrameBufferCache* sharedCache()

  /**
   * Initialize the cache using the specified size and count;
   */
  FrameBufferCache(const Size& rtt_size, int count);
  ~FrameBufferCache();
  
  FrameBuffer * ReserveBuffer();
  void RecycleBuffer(FrameBuffer * buffer);

 private:
	GenerateBuffers(int count);
	
	vector<FrameBuffer *> buffers_;
	Size rtt_size_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_FRAMEBUFFERCACHE_H_