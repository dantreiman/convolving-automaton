CC = /usr/bin/c++

LIB_SRCS = Engine.cc \
           FFT.cc \
           FrameBuffer.cc \
           FrameBufferCache.cc \
           FrameBufferRing.cc \
           OpenGLTimer.cc \
           Kernel.cc \
           Renderer.cc \
           Simulation.cc \
           Shader.cc \
           ShaderAttributes.cc \
           SLParameters.cc \
           StopWatch.cc \
           Timer.cc \
           VertexArray.cc \
           glfw-3.1.1/build/src/libglfw3.a

MAIN_SRCS = main.cc \
            $(LIB_SRCS)

TEST_PERF_SRCS = profile_main.cc \
                 $(LIB_SRCS)

LINKER_FLAGS = -lc++
LINKER_FLAGS_OSX = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
C_FLAGS = -std=c++11 -I glfw-3.1.1/include

automaton:
	$(CC) $(MAIN_SRCS) $(C_FLAGS) $(LINKER_FLAGS) $(LINKER_FLAGS_OSX) -o convolving_automaton

perftest:
	$(CC) $(TEST_PERF_SRCS) $(C_FLAGS) $(LINKER_FLAGS) $(LINKER_FLAGS_OSX) -o perf_test

run: all
	./convolving_automaton