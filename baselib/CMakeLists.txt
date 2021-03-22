set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library (baselib 
    FileLogger.cpp
    OutputWindow.cpp
    Utils.cpp
    log.cpp
    )

list(APPEND EXTRA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(baselib PUBLIC ${EXTRA_INCLUDES} )
