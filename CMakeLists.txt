cmake_minimum_required(VERSION 2.6)
project(copengl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

macro(link_to_library PROJNAME LIBNAME)
    include_directories(${${LIBNAME}_INCLUDE_DIR})
    target_link_libraries(${PROJNAME} ${${LIBNAME}_LIBRARY})
endmacro()

add_subdirectory(ch2)
