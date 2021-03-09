cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(test VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#list(APPEND EXTRA_INCLUDES ../../Arduino/ArduinoLinuxCompatibilityLib)

#list(APPEND EXTRA_INCLUDES ../../Arduino/FlashDataStorageLib)

# add the executable target
add_executable(test test.cpp)

# Specify the includes and libs for the executable target
#target_include_directories(test PUBLIC ${EXTRA_INCLUDES} )
#target_link_libraries(test_summarizer PUBLIC ArduinoLinuxCompatibilityLib FlashDataStorageLib)
