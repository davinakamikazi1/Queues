# Set minimum CMAKE
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project( QueuesAssignment )

# require C++20
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( APP_EXECUTABLE QueuesTest )

set( LIB_NAME classLibrary )

# Add the Stack class
# Add the class .cpp and .h files
add_library( ${LIB_NAME} INTERFACE  )
target_sources(${LIB_NAME}
    INTERFACE
        inc/queues.hpp
)

target_include_directories( ${LIB_NAME} INTERFACE inc )

ADD_EXECUTABLE( ${APP_EXECUTABLE} src/queuesTest.cpp )
TARGET_LINK_LIBRARIES( ${APP_EXECUTABLE} ${LIB_NAME} )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_EXECUTABLE} )

include (CTest)
add_test(${APP_EXECUTABLE}_testQueueForCS2420 ${APP_EXECUTABLE} 1)
add_test(${APP_EXECUTABLE}_testQueueClone ${APP_EXECUTABLE} 2)

find_program(VALGRIND "valgrind")
if(VALGRIND)
	add_custom_target(valgrind
		COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --error-exitcode=1 $<TARGET_FILE:${APP_EXECUTABLE}>)
endif()