add_executable(ch2_1 ch2_1.cpp)
link_to_library(ch2_1 GLFW3)

add_executable(ch2_2 ch2_2.cpp)
link_to_library(ch2_2 GLFW3)

add_executable(ch2_3 ch2_3.cpp)
link_to_library(ch2_3 GLEW)
link_to_library(ch2_3 GLFW3)
