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
include baselib/CMakeFiles/baselib.dir/depend.make

# Include the progress variables for this target.
include baselib/CMakeFiles/baselib.dir/progress.make

# Include the compile flags for this target's objects.
include baselib/CMakeFiles/baselib.dir/flags.make

baselib/CMakeFiles/baselib.dir/FileLogger.cpp.o: baselib/CMakeFiles/baselib.dir/flags.make
baselib/CMakeFiles/baselib.dir/FileLogger.cpp.o: ../baselib/FileLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object baselib/CMakeFiles/baselib.dir/FileLogger.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/baselib.dir/FileLogger.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/baselib/FileLogger.cpp

baselib/CMakeFiles/baselib.dir/FileLogger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/baselib.dir/FileLogger.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/baselib/FileLogger.cpp > CMakeFiles/baselib.dir/FileLogger.cpp.i

baselib/CMakeFiles/baselib.dir/FileLogger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/baselib.dir/FileLogger.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/baselib/FileLogger.cpp -o CMakeFiles/baselib.dir/FileLogger.cpp.s

baselib/CMakeFiles/baselib.dir/OutputWindow.cpp.o: baselib/CMakeFiles/baselib.dir/flags.make
baselib/CMakeFiles/baselib.dir/OutputWindow.cpp.o: ../baselib/OutputWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object baselib/CMakeFiles/baselib.dir/OutputWindow.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/baselib.dir/OutputWindow.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/baselib/OutputWindow.cpp

baselib/CMakeFiles/baselib.dir/OutputWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/baselib.dir/OutputWindow.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/baselib/OutputWindow.cpp > CMakeFiles/baselib.dir/OutputWindow.cpp.i

baselib/CMakeFiles/baselib.dir/OutputWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/baselib.dir/OutputWindow.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/baselib/OutputWindow.cpp -o CMakeFiles/baselib.dir/OutputWindow.cpp.s

baselib/CMakeFiles/baselib.dir/Utils.cpp.o: baselib/CMakeFiles/baselib.dir/flags.make
baselib/CMakeFiles/baselib.dir/Utils.cpp.o: ../baselib/Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object baselib/CMakeFiles/baselib.dir/Utils.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/baselib.dir/Utils.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/baselib/Utils.cpp

baselib/CMakeFiles/baselib.dir/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/baselib.dir/Utils.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/baselib/Utils.cpp > CMakeFiles/baselib.dir/Utils.cpp.i

baselib/CMakeFiles/baselib.dir/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/baselib.dir/Utils.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/baselib/Utils.cpp -o CMakeFiles/baselib.dir/Utils.cpp.s

baselib/CMakeFiles/baselib.dir/log.cpp.o: baselib/CMakeFiles/baselib.dir/flags.make
baselib/CMakeFiles/baselib.dir/log.cpp.o: ../baselib/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object baselib/CMakeFiles/baselib.dir/log.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/baselib.dir/log.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/baselib/log.cpp

baselib/CMakeFiles/baselib.dir/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/baselib.dir/log.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/baselib/log.cpp > CMakeFiles/baselib.dir/log.cpp.i

baselib/CMakeFiles/baselib.dir/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/baselib.dir/log.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/baselib/log.cpp -o CMakeFiles/baselib.dir/log.cpp.s

# Object files for target baselib
baselib_OBJECTS = \
"CMakeFiles/baselib.dir/FileLogger.cpp.o" \
"CMakeFiles/baselib.dir/OutputWindow.cpp.o" \
"CMakeFiles/baselib.dir/Utils.cpp.o" \
"CMakeFiles/baselib.dir/log.cpp.o"

# External object files for target baselib
baselib_EXTERNAL_OBJECTS =

baselib/libbaselib.a: baselib/CMakeFiles/baselib.dir/FileLogger.cpp.o
baselib/libbaselib.a: baselib/CMakeFiles/baselib.dir/OutputWindow.cpp.o
baselib/libbaselib.a: baselib/CMakeFiles/baselib.dir/Utils.cpp.o
baselib/libbaselib.a: baselib/CMakeFiles/baselib.dir/log.cpp.o
baselib/libbaselib.a: baselib/CMakeFiles/baselib.dir/build.make
baselib/libbaselib.a: baselib/CMakeFiles/baselib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libbaselib.a"
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && $(CMAKE_COMMAND) -P CMakeFiles/baselib.dir/cmake_clean_target.cmake
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/baselib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
baselib/CMakeFiles/baselib.dir/build: baselib/libbaselib.a

.PHONY : baselib/CMakeFiles/baselib.dir/build

baselib/CMakeFiles/baselib.dir/clean:
	cd /home/dave/Documents/GitHub/GrblUtils/build/baselib && $(CMAKE_COMMAND) -P CMakeFiles/baselib.dir/cmake_clean.cmake
.PHONY : baselib/CMakeFiles/baselib.dir/clean

baselib/CMakeFiles/baselib.dir/depend:
	cd /home/dave/Documents/GitHub/GrblUtils/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dave/Documents/GitHub/GrblUtils /home/dave/Documents/GitHub/GrblUtils/baselib /home/dave/Documents/GitHub/GrblUtils/build /home/dave/Documents/GitHub/GrblUtils/build/baselib /home/dave/Documents/GitHub/GrblUtils/build/baselib/CMakeFiles/baselib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : baselib/CMakeFiles/baselib.dir/depend

