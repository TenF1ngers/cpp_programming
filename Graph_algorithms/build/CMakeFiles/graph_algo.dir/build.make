# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/build

# Include any dependencies generated for this target.
include CMakeFiles/graph_algo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/graph_algo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/graph_algo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graph_algo.dir/flags.make

CMakeFiles/graph_algo.dir/chemistry.cpp.o: CMakeFiles/graph_algo.dir/flags.make
CMakeFiles/graph_algo.dir/chemistry.cpp.o: /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/chemistry.cpp
CMakeFiles/graph_algo.dir/chemistry.cpp.o: CMakeFiles/graph_algo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/graph_algo.dir/chemistry.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/graph_algo.dir/chemistry.cpp.o -MF CMakeFiles/graph_algo.dir/chemistry.cpp.o.d -o CMakeFiles/graph_algo.dir/chemistry.cpp.o -c /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/chemistry.cpp

CMakeFiles/graph_algo.dir/chemistry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph_algo.dir/chemistry.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/chemistry.cpp > CMakeFiles/graph_algo.dir/chemistry.cpp.i

CMakeFiles/graph_algo.dir/chemistry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph_algo.dir/chemistry.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/chemistry.cpp -o CMakeFiles/graph_algo.dir/chemistry.cpp.s

# Object files for target graph_algo
graph_algo_OBJECTS = \
"CMakeFiles/graph_algo.dir/chemistry.cpp.o"

# External object files for target graph_algo
graph_algo_EXTERNAL_OBJECTS =

graph_algo: CMakeFiles/graph_algo.dir/chemistry.cpp.o
graph_algo: CMakeFiles/graph_algo.dir/build.make
graph_algo: CMakeFiles/graph_algo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable graph_algo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graph_algo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graph_algo.dir/build: graph_algo
.PHONY : CMakeFiles/graph_algo.dir/build

CMakeFiles/graph_algo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graph_algo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graph_algo.dir/clean

CMakeFiles/graph_algo.dir/depend:
	cd /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/build /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/build /Users/ex3nd/TenF1ngers_profile/cpp_programming/Graph_algorithms/build/CMakeFiles/graph_algo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graph_algo.dir/depend

