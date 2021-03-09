set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library (screenlib 
    screen.cpp
    )

list(APPEND EXTRA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(screenlib PUBLIC ${EXTRA_INCLUDES} )
