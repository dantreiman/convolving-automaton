CC = /usr/bin/c++

LIB_SRCS = source/automaton/KernelGenerator.cc \
           source/fft/FFT.cc \
           source/glfw_frontend/Engine.cc \
           source/glfw_frontend/ImageCapture.cc \
           source/glfw_frontend/Renderer.cc \
           source/gl_utilities/FrameBuffer.cc \
           source/gl_utilities/FrameBufferCache.cc \
           source/gl_utilities/OpenGLTimer.cc \
           source/gl_utilities/Shader.cc \
           source/gl_utilities/ShaderAttributes.cc \
           source/gl_utilities/VertexArray.cc \
           source/simulation/FrameBufferRing.cc \
           source/simulation/Simulation.cc \
           source/utilities/StopWatch.cc \
           glfw-3.1.1/build/src/libglfw3.a

MAIN_SRCS = source/glfw_frontend/main.cc \
            $(LIB_SRCS)

TEST_PERF_SRCS = source/glfw_frontend/profile_main.cc \
                 $(LIB_SRCS)

LINKER_FLAGS = -lc++
LINKER_FLAGS_OSX = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
C_FLAGS = -std=c++11 -I glfw-3.1.1/include -I cimg -I source -I source/utilities -I source/gl_utilities \
-I source/automaton -I source/simulation -I glfw_frontend -I source/fft

automaton:
	$(CC) $(MAIN_SRCS) $(C_FLAGS) $(LINKER_FLAGS) $(LINKER_FLAGS_OSX) -o convolving_automaton

perftest:
	$(CC) $(TEST_PERF_SRCS) $(C_FLAGS) $(LINKER_FLAGS) $(LINKER_FLAGS_OSX) -o perf_test

run: all
	./convolving_automaton