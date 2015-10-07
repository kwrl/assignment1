cmake_minimum_required(VERSION 2.8)
project(Assignment1)
set(CMAKE_BUILD_TYPE Debug)

ADD_DEFINITIONS(
    -std=c++11
)

find_package( OpenCV REQUIRED )
include_directories( core/  )
add_executable(Assignment1 core/main.cpp)
target_link_libraries( Assignment1 ${OpenCV_LIBS} )
