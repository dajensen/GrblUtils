set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library (inputlib 
    keyboard.cpp
    )

list(APPEND EXTRA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(inputlib PUBLIC ${EXTRA_INCLUDES} )
