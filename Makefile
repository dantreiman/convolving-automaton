CC = /usr/bin/c++

SRCS =  main.cc \
		Engine.cc \
		Renderer.cc \
		Kernel.cc \
		glfw-3.1.1/build/src/libglfw3.a

LINKER_FLAGS = -lc++
LINKER_FLAGS_OSX = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
C_FLAGS = -std=c++11 -I glfw-3.1.1/include

all:
	$(CC) $(SRCS) $(C_FLAGS) $(LINKER_FLAGS) $(LINKER_FLAGS_OSX) -o convolving_automaton

run: all
	./convolving_automaton