set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library (inputlib 
        input.cpp
        keyboard.cpp
        gamepad.cpp
    )

find_package (PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)
if(LIBEVDEV_FOUND)
        message(STATUS "libevdev found")
        message(STATUS "libevdev includes: ${LIBEVDEV_INCLUDE_DIRS}")
endif()

list(APPEND EXTRA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

# This library uses the baselib functionality.  So if you link this one, you must also link in baselib.
list(APPEND EXTRA_INCLUDES ../baselib)

list(APPEND EXTRA_INCLUDES ${LIBEVDEV_INCLUDE_DIRS})
list(APPEND EXTRA_LIBS ${LIBEVDEV_LIBRARIES})

target_include_directories(inputlib PUBLIC ${EXTRA_INCLUDES} )
