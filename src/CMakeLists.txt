add_library(src app.cpp apps_init.cpp apps_vao.cpp apps_xyzw.cpp shader.cpp)
target_include_directories(src PUBLIC ${INCLUDE_DIR})