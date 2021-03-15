cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(JoystickTest VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package (PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)
if(LIBEVDEV_FOUND)
        message(STATUS "libevdev found")
        message(STATUS "libevdev includes: ${LIBEVDEV_INCLUDE_DIRS}")
endif()

list(APPEND EXTRA_INCLUDES ${LIBEVDEV_INCLUDE_DIRS})
list(APPEND EXTRA_INCLUDES baselib)

list(APPEND EXTRA_LIBS ${LIBEVDEV_LIBRARIES})
list(APPEND EXTRA_LIBS baselib)

# add the executable target
add_executable(JoystickTest 
                        JoystickTest.cpp 
                )

# Specify the includes and libs for the executable target
target_include_directories(JoystickTest PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(JoystickTest PUBLIC ${EXTRA_LIBS})
