# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/dave/tools/cmake-3.19.2-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/dave/tools/cmake-3.19.2-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dave/Documents/GitHub/GrblUtils

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dave/Documents/GitHub/GrblUtils/build

# Include any dependencies generated for this target.
include JoystickTest/CMakeFiles/JoystickTest.dir/depend.make

# Include the progress variables for this target.
include JoystickTest/CMakeFiles/JoystickTest.dir/progress.make

# Include the compile flags for this target's objects.
include JoystickTest/CMakeFiles/JoystickTest.dir/flags.make

JoystickTest/CMakeFiles/JoystickTest.dir/JoystickTest.cpp.o: JoystickTest/CMakeFiles/JoystickTest.dir/flags.make
JoystickTest/CMakeFiles/JoystickTest.dir/JoystickTest.cpp.o: ../JoystickTest/JoystickTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object JoystickTest/CMakeFiles/JoystickTest.dir/JoystickTest.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/JoystickTest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/JoystickTest.dir/JoystickTest.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/JoystickTest/JoystickTest.cpp

JoystickTest/CMakeFiles/JoystickTest.dir/JoystickTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JoystickTest.dir/JoystickTest.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/JoystickTest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/JoystickTest/JoystickTest.cpp > CMakeFiles/JoystickTest.dir/JoystickTest.cpp.i

JoystickTest/CMakeFiles/JoystickTest.dir/JoystickTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JoystickTest.dir/JoystickTest.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/JoystickTest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/JoystickTest/JoystickTest.cpp -o CMakeFiles/JoystickTest.dir/JoystickTest.cpp.s

# Object files for target JoystickTest
JoystickTest_OBJECTS = \
"CMakeFiles/JoystickTest.dir/JoystickTest.cpp.o"

# External object files for target JoystickTest
JoystickTest_EXTERNAL_OBJECTS =

../bin/JoystickTest: JoystickTest/CMakeFiles/JoystickTest.dir/JoystickTest.cpp.o
../bin/JoystickTest: JoystickTest/CMakeFiles/JoystickTest.dir/build.make
../bin/JoystickTest: baselib/libbaselib.a
../bin/JoystickTest: JoystickTest/CMakeFiles/JoystickTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/JoystickTest"
	cd /home/dave/Documents/GitHub/GrblUtils/build/JoystickTest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JoystickTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
JoystickTest/CMakeFiles/JoystickTest.dir/build: ../bin/JoystickTest

.PHONY : JoystickTest/CMakeFiles/JoystickTest.dir/build

JoystickTest/CMakeFiles/JoystickTest.dir/clean:
	cd /home/dave/Documents/GitHub/GrblUtils/build/JoystickTest && $(CMAKE_COMMAND) -P CMakeFiles/JoystickTest.dir/cmake_clean.cmake
.PHONY : JoystickTest/CMakeFiles/JoystickTest.dir/clean

JoystickTest/CMakeFiles/JoystickTest.dir/depend:
	cd /home/dave/Documents/GitHub/GrblUtils/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dave/Documents/GitHub/GrblUtils /home/dave/Documents/GitHub/GrblUtils/JoystickTest /home/dave/Documents/GitHub/GrblUtils/build /home/dave/Documents/GitHub/GrblUtils/build/JoystickTest /home/dave/Documents/GitHub/GrblUtils/build/JoystickTest/CMakeFiles/JoystickTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : JoystickTest/CMakeFiles/JoystickTest.dir/depend

