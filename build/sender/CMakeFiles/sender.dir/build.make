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
include sender/CMakeFiles/sender.dir/depend.make

# Include the progress variables for this target.
include sender/CMakeFiles/sender.dir/progress.make

# Include the compile flags for this target's objects.
include sender/CMakeFiles/sender.dir/flags.make

sender/CMakeFiles/sender.dir/sender.cpp.o: sender/CMakeFiles/sender.dir/flags.make
sender/CMakeFiles/sender.dir/sender.cpp.o: ../sender/sender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sender/CMakeFiles/sender.dir/sender.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sender.dir/sender.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/sender/sender.cpp

sender/CMakeFiles/sender.dir/sender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sender.dir/sender.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/sender/sender.cpp > CMakeFiles/sender.dir/sender.cpp.i

sender/CMakeFiles/sender.dir/sender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sender.dir/sender.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/sender/sender.cpp -o CMakeFiles/sender.dir/sender.cpp.s

sender/CMakeFiles/sender.dir/StatusListener.cpp.o: sender/CMakeFiles/sender.dir/flags.make
sender/CMakeFiles/sender.dir/StatusListener.cpp.o: ../sender/StatusListener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object sender/CMakeFiles/sender.dir/StatusListener.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sender.dir/StatusListener.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/sender/StatusListener.cpp

sender/CMakeFiles/sender.dir/StatusListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sender.dir/StatusListener.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/sender/StatusListener.cpp > CMakeFiles/sender.dir/StatusListener.cpp.i

sender/CMakeFiles/sender.dir/StatusListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sender.dir/StatusListener.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/sender/StatusListener.cpp -o CMakeFiles/sender.dir/StatusListener.cpp.s

sender/CMakeFiles/sender.dir/LineReader.cpp.o: sender/CMakeFiles/sender.dir/flags.make
sender/CMakeFiles/sender.dir/LineReader.cpp.o: ../sender/LineReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object sender/CMakeFiles/sender.dir/LineReader.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sender.dir/LineReader.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/sender/LineReader.cpp

sender/CMakeFiles/sender.dir/LineReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sender.dir/LineReader.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/sender/LineReader.cpp > CMakeFiles/sender.dir/LineReader.cpp.i

sender/CMakeFiles/sender.dir/LineReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sender.dir/LineReader.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/sender/LineReader.cpp -o CMakeFiles/sender.dir/LineReader.cpp.s

sender/CMakeFiles/sender.dir/GcodeCommunicator.cpp.o: sender/CMakeFiles/sender.dir/flags.make
sender/CMakeFiles/sender.dir/GcodeCommunicator.cpp.o: ../sender/GcodeCommunicator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object sender/CMakeFiles/sender.dir/GcodeCommunicator.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sender.dir/GcodeCommunicator.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/sender/GcodeCommunicator.cpp

sender/CMakeFiles/sender.dir/GcodeCommunicator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sender.dir/GcodeCommunicator.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/sender/GcodeCommunicator.cpp > CMakeFiles/sender.dir/GcodeCommunicator.cpp.i

sender/CMakeFiles/sender.dir/GcodeCommunicator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sender.dir/GcodeCommunicator.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/sender/GcodeCommunicator.cpp -o CMakeFiles/sender.dir/GcodeCommunicator.cpp.s

sender/CMakeFiles/sender.dir/EmptyListener.cpp.o: sender/CMakeFiles/sender.dir/flags.make
sender/CMakeFiles/sender.dir/EmptyListener.cpp.o: ../sender/EmptyListener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object sender/CMakeFiles/sender.dir/EmptyListener.cpp.o"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sender.dir/EmptyListener.cpp.o -c /home/dave/Documents/GitHub/GrblUtils/sender/EmptyListener.cpp

sender/CMakeFiles/sender.dir/EmptyListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sender.dir/EmptyListener.cpp.i"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave/Documents/GitHub/GrblUtils/sender/EmptyListener.cpp > CMakeFiles/sender.dir/EmptyListener.cpp.i

sender/CMakeFiles/sender.dir/EmptyListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sender.dir/EmptyListener.cpp.s"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave/Documents/GitHub/GrblUtils/sender/EmptyListener.cpp -o CMakeFiles/sender.dir/EmptyListener.cpp.s

# Object files for target sender
sender_OBJECTS = \
"CMakeFiles/sender.dir/sender.cpp.o" \
"CMakeFiles/sender.dir/StatusListener.cpp.o" \
"CMakeFiles/sender.dir/LineReader.cpp.o" \
"CMakeFiles/sender.dir/GcodeCommunicator.cpp.o" \
"CMakeFiles/sender.dir/EmptyListener.cpp.o"

# External object files for target sender
sender_EXTERNAL_OBJECTS =

../bin/sender: sender/CMakeFiles/sender.dir/sender.cpp.o
../bin/sender: sender/CMakeFiles/sender.dir/StatusListener.cpp.o
../bin/sender: sender/CMakeFiles/sender.dir/LineReader.cpp.o
../bin/sender: sender/CMakeFiles/sender.dir/GcodeCommunicator.cpp.o
../bin/sender: sender/CMakeFiles/sender.dir/EmptyListener.cpp.o
../bin/sender: sender/CMakeFiles/sender.dir/build.make
../bin/sender: /usr/lib/x86_64-linux-gnu/libcurses.so
../bin/sender: /usr/lib/x86_64-linux-gnu/libform.so
../bin/sender: seriallib/libseriallib.a
../bin/sender: screenlib/libscreenlib.a
../bin/sender: inputlib/libinputlib.a
../bin/sender: baselib/libbaselib.a
../bin/sender: /usr/lib/x86_64-linux-gnu/libcurses.so
../bin/sender: /usr/lib/x86_64-linux-gnu/libform.so
../bin/sender: sender/CMakeFiles/sender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dave/Documents/GitHub/GrblUtils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../../bin/sender"
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sender/CMakeFiles/sender.dir/build: ../bin/sender

.PHONY : sender/CMakeFiles/sender.dir/build

sender/CMakeFiles/sender.dir/clean:
	cd /home/dave/Documents/GitHub/GrblUtils/build/sender && $(CMAKE_COMMAND) -P CMakeFiles/sender.dir/cmake_clean.cmake
.PHONY : sender/CMakeFiles/sender.dir/clean

sender/CMakeFiles/sender.dir/depend:
	cd /home/dave/Documents/GitHub/GrblUtils/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dave/Documents/GitHub/GrblUtils /home/dave/Documents/GitHub/GrblUtils/sender /home/dave/Documents/GitHub/GrblUtils/build /home/dave/Documents/GitHub/GrblUtils/build/sender /home/dave/Documents/GitHub/GrblUtils/build/sender/CMakeFiles/sender.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sender/CMakeFiles/sender.dir/depend
