set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library (seriallib 
    SerialDataIo.cpp
    GrblCommunicator.cpp
    GrblReply.cpp
    GrblReplyDispatcher.cpp
    AxisNames.cpp
    Replies/Status.cpp
    )

list(APPEND EXTRA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

# This library uses the baselib functionality.  So if you link this one, you must also link in baselib.
list(APPEND EXTRA_INCLUDES ../baselib)

target_include_directories(seriallib PUBLIC ${EXTRA_INCLUDES} )
