cmake_minimum_required(VERSION 3.0.0)
project(test23 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

find_package (Threads REQUIRED)
find_package(SDL2 REQUIRED)

set(CTRE_OBJECTS 
	libCTRE_PhoenixCCI.so
	libCTRE_Phoenix.so
	)

    #define include directory for CTRE .so's that get manually installed
set(PHOENIX_LIBRARY_PATH /home/lunabotics23/testing/lib)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(test23 main.cpp)

#add_library()

target_include_directories(test23 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
