# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/esikora/SPD/SPD2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esikora/SPD/SPD2/build

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/src/problem.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/problem.cpp.o: ../src/problem.cpp
CMakeFiles/engine.dir/src/problem.cpp.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esikora/SPD/SPD2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/src/problem.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/src/problem.cpp.o -MF CMakeFiles/engine.dir/src/problem.cpp.o.d -o CMakeFiles/engine.dir/src/problem.cpp.o -c /home/esikora/SPD/SPD2/src/problem.cpp

CMakeFiles/engine.dir/src/problem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/problem.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/esikora/SPD/SPD2/src/problem.cpp > CMakeFiles/engine.dir/src/problem.cpp.i

CMakeFiles/engine.dir/src/problem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/problem.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/esikora/SPD/SPD2/src/problem.cpp -o CMakeFiles/engine.dir/src/problem.cpp.s

CMakeFiles/engine.dir/src/instance.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/instance.cpp.o: ../src/instance.cpp
CMakeFiles/engine.dir/src/instance.cpp.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esikora/SPD/SPD2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/engine.dir/src/instance.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/src/instance.cpp.o -MF CMakeFiles/engine.dir/src/instance.cpp.o.d -o CMakeFiles/engine.dir/src/instance.cpp.o -c /home/esikora/SPD/SPD2/src/instance.cpp

CMakeFiles/engine.dir/src/instance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/instance.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/esikora/SPD/SPD2/src/instance.cpp > CMakeFiles/engine.dir/src/instance.cpp.i

CMakeFiles/engine.dir/src/instance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/instance.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/esikora/SPD/SPD2/src/instance.cpp -o CMakeFiles/engine.dir/src/instance.cpp.s

engine: CMakeFiles/engine.dir/src/problem.cpp.o
engine: CMakeFiles/engine.dir/src/instance.cpp.o
engine: CMakeFiles/engine.dir/build.make
.PHONY : engine

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine
.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd /home/esikora/SPD/SPD2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esikora/SPD/SPD2 /home/esikora/SPD/SPD2 /home/esikora/SPD/SPD2/build /home/esikora/SPD/SPD2/build /home/esikora/SPD/SPD2/build/CMakeFiles/engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/engine.dir/depend

