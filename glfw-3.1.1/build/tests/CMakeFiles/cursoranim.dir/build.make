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
include tests/CMakeFiles/cursoranim.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/cursoranim.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/cursoranim.dir/flags.make

tests/CMakeFiles/cursoranim.dir/cursoranim.c.o: tests/CMakeFiles/cursoranim.dir/flags.make
tests/CMakeFiles/cursoranim.dir/cursoranim.c.o: ../tests/cursoranim.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/cursoranim.dir/cursoranim.c.o"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/cursoranim.dir/cursoranim.c.o   -c "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests/cursoranim.c"

tests/CMakeFiles/cursoranim.dir/cursoranim.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cursoranim.dir/cursoranim.c.i"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests/cursoranim.c" > CMakeFiles/cursoranim.dir/cursoranim.c.i

tests/CMakeFiles/cursoranim.dir/cursoranim.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cursoranim.dir/cursoranim.c.s"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests/cursoranim.c" -o CMakeFiles/cursoranim.dir/cursoranim.c.s

tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.requires:
.PHONY : tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.requires

tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.provides: tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.requires
	$(MAKE) -f tests/CMakeFiles/cursoranim.dir/build.make tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.provides.build
.PHONY : tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.provides

tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.provides.build: tests/CMakeFiles/cursoranim.dir/cursoranim.c.o

# Object files for target cursoranim
cursoranim_OBJECTS = \
"CMakeFiles/cursoranim.dir/cursoranim.c.o"

# External object files for target cursoranim
cursoranim_EXTERNAL_OBJECTS =

tests/cursoranim.app/Contents/MacOS/cursoranim: tests/CMakeFiles/cursoranim.dir/cursoranim.c.o
tests/cursoranim.app/Contents/MacOS/cursoranim: tests/CMakeFiles/cursoranim.dir/build.make
tests/cursoranim.app/Contents/MacOS/cursoranim: src/libglfw3.a
tests/cursoranim.app/Contents/MacOS/cursoranim: tests/CMakeFiles/cursoranim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable cursoranim.app/Contents/MacOS/cursoranim"
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cursoranim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/cursoranim.dir/build: tests/cursoranim.app/Contents/MacOS/cursoranim
.PHONY : tests/CMakeFiles/cursoranim.dir/build

tests/CMakeFiles/cursoranim.dir/requires: tests/CMakeFiles/cursoranim.dir/cursoranim.c.o.requires
.PHONY : tests/CMakeFiles/cursoranim.dir/requires

tests/CMakeFiles/cursoranim.dir/clean:
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" && $(CMAKE_COMMAND) -P CMakeFiles/cursoranim.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/cursoranim.dir/clean

tests/CMakeFiles/cursoranim.dir/depend:
	cd "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/tests" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests" "/Users/dtreiman/Desktop/Math/Smooth Life/shader/glfw-3.1.1/build/tests/CMakeFiles/cursoranim.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/cursoranim.dir/depend

