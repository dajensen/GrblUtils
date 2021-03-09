cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(jogger VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)

list(APPEND EXTRA_INCLUDES ${CURSES_INCLUDE_DIR})
list(APPEND EXTRA_INCLUDES seriallib)
list(APPEND EXTRA_INCLUDES screenlib)
list(APPEND EXTRA_INCLUDES inputlib)
list(APPEND EXTRA_INCLUDES baselib)

list(APPEND EXTRA_LIBS ${CURSES_LIBRARIES})
list(APPEND EXTRA_LIBS seriallib)
list(APPEND EXTRA_LIBS screenlib)
list(APPEND EXTRA_LIBS inputlib)
list(APPEND EXTRA_LIBS baselib)

# add the executable target
add_executable(jogger 
                        jogger.cpp 
                        axis.cpp 
                        valuedisplay.cpp
                        axisreport.cpp
                        toppanel.cpp 
                        InitStatusListener.cpp
                )

# Specify the includes and libs for the executable target
target_include_directories(jogger PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(jogger PUBLIC ${EXTRA_LIBS})
