cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(downloader VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Build the libraries
add_subdirectory(seriallib)
add_subdirectory(screenlib)
add_subdirectory(inputlib)
add_subdirectory(baselib)

# Build the executables that use the libraries
add_subdirectory(jogger)
add_subdirectory(sender)
add_subdirectory(test)

add_subdirectory(JoystickTest)
