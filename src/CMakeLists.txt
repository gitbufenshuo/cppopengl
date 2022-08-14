add_compile_options(-Wno-unused-function)
add_library(src app.cpp apps_init.cpp apps_vao.cpp apps_xyzw.cpp apps_math.cpp shader.cpp)
target_include_directories(src PUBLIC ${INCLUDE_DIR})