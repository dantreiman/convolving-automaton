# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Applications/CMake 2.8-9.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-9.app/Contents/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-9.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build"

# Include any dependencies generated for this target.
include examples/CMakeFiles/Particles.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Particles.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Particles.dir/flags.make

examples/CMakeFiles/Particles.dir/particles.c.o: examples/CMakeFiles/Particles.dir/flags.make
examples/CMakeFiles/Particles.dir/particles.c.o: ../examples/particles.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/Particles.dir/particles.c.o"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/Particles.dir/particles.c.o   -c "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/examples/particles.c"

examples/CMakeFiles/Particles.dir/particles.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Particles.dir/particles.c.i"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/examples/particles.c" > CMakeFiles/Particles.dir/particles.c.i

examples/CMakeFiles/Particles.dir/particles.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Particles.dir/particles.c.s"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/examples/particles.c" -o CMakeFiles/Particles.dir/particles.c.s

examples/CMakeFiles/Particles.dir/particles.c.o.requires:
.PHONY : examples/CMakeFiles/Particles.dir/particles.c.o.requires

examples/CMakeFiles/Particles.dir/particles.c.o.provides: examples/CMakeFiles/Particles.dir/particles.c.o.requires
	$(MAKE) -f examples/CMakeFiles/Particles.dir/build.make examples/CMakeFiles/Particles.dir/particles.c.o.provides.build
.PHONY : examples/CMakeFiles/Particles.dir/particles.c.o.provides

examples/CMakeFiles/Particles.dir/particles.c.o.provides.build: examples/CMakeFiles/Particles.dir/particles.c.o

examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o: examples/CMakeFiles/Particles.dir/flags.make
examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o: ../deps/tinycthread.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/Particles.dir/__/deps/tinycthread.c.o   -c "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/deps/tinycthread.c"

examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Particles.dir/__/deps/tinycthread.c.i"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/deps/tinycthread.c" > CMakeFiles/Particles.dir/__/deps/tinycthread.c.i

examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Particles.dir/__/deps/tinycthread.c.s"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/deps/tinycthread.c" -o CMakeFiles/Particles.dir/__/deps/tinycthread.c.s

examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.requires:
.PHONY : examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.requires

examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.provides: examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.requires
	$(MAKE) -f examples/CMakeFiles/Particles.dir/build.make examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.provides.build
.PHONY : examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.provides

examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.provides.build: examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o

# Object files for target Particles
Particles_OBJECTS = \
"CMakeFiles/Particles.dir/particles.c.o" \
"CMakeFiles/Particles.dir/__/deps/tinycthread.c.o"

# External object files for target Particles
Particles_EXTERNAL_OBJECTS =

examples/Particles.app/Contents/MacOS/Particles: examples/CMakeFiles/Particles.dir/particles.c.o
examples/Particles.app/Contents/MacOS/Particles: examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o
examples/Particles.app/Contents/MacOS/Particles: examples/CMakeFiles/Particles.dir/build.make
examples/Particles.app/Contents/MacOS/Particles: src/libglfw3.a
examples/Particles.app/Contents/MacOS/Particles: examples/CMakeFiles/Particles.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable Particles.app/Contents/MacOS/Particles"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Particles.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Particles.dir/build: examples/Particles.app/Contents/MacOS/Particles
.PHONY : examples/CMakeFiles/Particles.dir/build

examples/CMakeFiles/Particles.dir/requires: examples/CMakeFiles/Particles.dir/particles.c.o.requires
examples/CMakeFiles/Particles.dir/requires: examples/CMakeFiles/Particles.dir/__/deps/tinycthread.c.o.requires
.PHONY : examples/CMakeFiles/Particles.dir/requires

examples/CMakeFiles/Particles.dir/clean:
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" && $(CMAKE_COMMAND) -P CMakeFiles/Particles.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Particles.dir/clean

examples/CMakeFiles/Particles.dir/depend:
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/examples" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/examples/CMakeFiles/Particles.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : examples/CMakeFiles/Particles.dir/depend
