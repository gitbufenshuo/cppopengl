cmake_minimum_required(VERSION 2.4)

project(hello_world)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/others/include)
set (GLFW_LIB ${PROJECT_SOURCE_DIR}/others/lib/libglfw.3.dylib)
set (GLAD_LIB ${PROJECT_SOURCE_DIR}/others/lib/libglad.dylib)
set (SELF_LIB ${PROJECT_SOURCE_DIR}/others/lib/libself.dylib)

add_subdirectory (src)

add_executable(mc.out main.cpp)
target_link_libraries (mc.out src ${SELF_LIB} ${GLFW_LIB} ${GLAD_LIB})
target_include_directories(
    mc.out
    PUBLIC
    ${INCLUDE_DIR}
)
