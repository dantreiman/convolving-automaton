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
include tests/CMakeFiles/threads.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/threads.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/threads.dir/flags.make

tests/CMakeFiles/threads.dir/threads.c.o: tests/CMakeFiles/threads.dir/flags.make
tests/CMakeFiles/threads.dir/threads.c.o: ../tests/threads.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/threads.dir/threads.c.o"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/threads.dir/threads.c.o   -c "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests/threads.c"

tests/CMakeFiles/threads.dir/threads.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/threads.c.i"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests/threads.c" > CMakeFiles/threads.dir/threads.c.i

tests/CMakeFiles/threads.dir/threads.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/threads.c.s"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests/threads.c" -o CMakeFiles/threads.dir/threads.c.s

tests/CMakeFiles/threads.dir/threads.c.o.requires:
.PHONY : tests/CMakeFiles/threads.dir/threads.c.o.requires

tests/CMakeFiles/threads.dir/threads.c.o.provides: tests/CMakeFiles/threads.dir/threads.c.o.requires
	$(MAKE) -f tests/CMakeFiles/threads.dir/build.make tests/CMakeFiles/threads.dir/threads.c.o.provides.build
.PHONY : tests/CMakeFiles/threads.dir/threads.c.o.provides

tests/CMakeFiles/threads.dir/threads.c.o.provides.build: tests/CMakeFiles/threads.dir/threads.c.o

tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: tests/CMakeFiles/threads.dir/flags.make
tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: ../deps/tinycthread.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/threads.dir/__/deps/tinycthread.c.o   -c "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/deps/tinycthread.c"

tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/__/deps/tinycthread.c.i"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/deps/tinycthread.c" > CMakeFiles/threads.dir/__/deps/tinycthread.c.i

tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/__/deps/tinycthread.c.s"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/deps/tinycthread.c" -o CMakeFiles/threads.dir/__/deps/tinycthread.c.s

tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.requires:
.PHONY : tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.requires

tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.provides: tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.requires
	$(MAKE) -f tests/CMakeFiles/threads.dir/build.make tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.provides.build
.PHONY : tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.provides

tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.provides.build: tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o

# Object files for target threads
threads_OBJECTS = \
"CMakeFiles/threads.dir/threads.c.o" \
"CMakeFiles/threads.dir/__/deps/tinycthread.c.o"

# External object files for target threads
threads_EXTERNAL_OBJECTS =

tests/threads.app/Contents/MacOS/threads: tests/CMakeFiles/threads.dir/threads.c.o
tests/threads.app/Contents/MacOS/threads: tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o
tests/threads.app/Contents/MacOS/threads: tests/CMakeFiles/threads.dir/build.make
tests/threads.app/Contents/MacOS/threads: src/libglfw3.a
tests/threads.app/Contents/MacOS/threads: tests/CMakeFiles/threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable threads.app/Contents/MacOS/threads"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/threads.dir/build: tests/threads.app/Contents/MacOS/threads
.PHONY : tests/CMakeFiles/threads.dir/build

tests/CMakeFiles/threads.dir/requires: tests/CMakeFiles/threads.dir/threads.c.o.requires
tests/CMakeFiles/threads.dir/requires: tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o.requires
.PHONY : tests/CMakeFiles/threads.dir/requires

tests/CMakeFiles/threads.dir/clean:
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && $(CMAKE_COMMAND) -P CMakeFiles/threads.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/threads.dir/clean

tests/CMakeFiles/threads.dir/depend:
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests/CMakeFiles/threads.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/threads.dir/depend

