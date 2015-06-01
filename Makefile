CC = /usr/bin/c++

SRCS =  main.cc \
		Engine.cc \
		FFT.cc \
		FrameBuffer.cc \
		FrameBufferCache.cc \
		FrameBufferRing.cc \
		Kernel.cc \
		Renderer.cc \
		Simulation.cc \
		Shader.cc \
		ShaderAttributes.cc \
		StopWatch.cc \
		VertexArray.cc \
		glfw-3.1.1/build/src/libglfw3.a

LINKER_FLAGS = -lc++
LINKER_FLAGS_OSX = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
C_FLAGS = -std=c++11 -I glfw-3.1.1/include

all:
	$(CC) $(SRCS) $(C_FLAGS) $(LINKER_FLAGS) $(LINKER_FLAGS_OSX) -o convolving_automaton

run: all
	./convolving_automaton