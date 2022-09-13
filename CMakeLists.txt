cmake_minimum_required(VERSION 2.4)


project(hello_world)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/others/include)
message(STATUS "Hello World : ${PROJECT_BINARY_DIR}" )



if (APPLE)
    set (GLFW_LIB ${PROJECT_SOURCE_DIR}/others/lib/libglfw.3.dylib)
    set (GLAD_LIB ${PROJECT_SOURCE_DIR}/others/lib/libglad.dylib)
    set (PROTO_LIB ${PROJECT_SOURCE_DIR}/others/lib/libprotobuf.a)
    set (CRYPTO_LIB ${PROJECT_SOURCE_DIR}/others/lib/libcrypto.lib)
    set (COLOR_BOLD "bold")
    set (COLOR_GREEN "green")
else()
    set (GLFW_LIB ${PROJECT_SOURCE_DIR}/others/lib/glfw3.dll)
    set (GLAD_LIB ${PROJECT_SOURCE_DIR}/others/lib/glad.dll)
    set (PROTO_LIB ${PROJECT_SOURCE_DIR}/others/lib/libprotobuf.lib)
    set (COLOR_BOLD "BOLD")
    set (COLOR_GREEN "GREEN")
endif()

configure_file(${PROJECT_SOURCE_DIR}/others/include/mc/config.h.in ${PROJECT_SOURCE_DIR}/others/include/mc/config.h)

add_subdirectory (src)

add_executable(mc.out main.cpp)

target_link_libraries (mc.out src 
    ${SELF_LIB} 
    ${GLFW_LIB} 
    ${GLAD_LIB}
    ${PROTO_LIB}
    ${CRYPTO_LIB}
)
target_include_directories(
    mc.out
    PUBLIC
    ${INCLUDE_DIR}
)
