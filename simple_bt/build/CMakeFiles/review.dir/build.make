# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/keti/behavior_tree_ws/simple_bt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/keti/behavior_tree_ws/simple_bt/build

# Include any dependencies generated for this target.
include CMakeFiles/review.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/review.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/review.dir/flags.make

CMakeFiles/review.dir/review.cpp.o: CMakeFiles/review.dir/flags.make
CMakeFiles/review.dir/review.cpp.o: ../review.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/keti/behavior_tree_ws/simple_bt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/review.dir/review.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/review.dir/review.cpp.o -c /home/keti/behavior_tree_ws/simple_bt/review.cpp

CMakeFiles/review.dir/review.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/review.dir/review.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/keti/behavior_tree_ws/simple_bt/review.cpp > CMakeFiles/review.dir/review.cpp.i

CMakeFiles/review.dir/review.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/review.dir/review.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/keti/behavior_tree_ws/simple_bt/review.cpp -o CMakeFiles/review.dir/review.cpp.s

# Object files for target review
review_OBJECTS = \
"CMakeFiles/review.dir/review.cpp.o"

# External object files for target review
review_EXTERNAL_OBJECTS =

review: CMakeFiles/review.dir/review.cpp.o
review: CMakeFiles/review.dir/build.make
review: /usr/local/lib/libbehaviortree_cpp.so
review: CMakeFiles/review.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/keti/behavior_tree_ws/simple_bt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable review"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/review.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/review.dir/build: review

.PHONY : CMakeFiles/review.dir/build

CMakeFiles/review.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/review.dir/cmake_clean.cmake
.PHONY : CMakeFiles/review.dir/clean

CMakeFiles/review.dir/depend:
	cd /home/keti/behavior_tree_ws/simple_bt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/keti/behavior_tree_ws/simple_bt /home/keti/behavior_tree_ws/simple_bt /home/keti/behavior_tree_ws/simple_bt/build /home/keti/behavior_tree_ws/simple_bt/build /home/keti/behavior_tree_ws/simple_bt/build/CMakeFiles/review.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/review.dir/depend

