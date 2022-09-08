set (MC_LOW_DIR mc/low/)
set(GAME_DIR game/)
set(EXAMPLE_DIR example/)
set(MC_COMM_DIR_DIR mc/comm/)
file(GLOB_RECURSE native_srcs ${MC_LOW_DIR}*.cpp)

file(GLOB_RECURSE all_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set (LOW_CODE 
${native_srcs}
)
set (COMM_CODE 
    ${MC_COMM_DIR_DIR}transform.pb.cc
)
set (TOOLS_CODE tools_image.cpp)
set (APPS_CODE 
    app.cpp
    apps_init.cpp 
    apps_vao.cpp 
    apps_xyzw.cpp
    apps_math.cpp
    apps_csv.cpp
    apps_camera.cpp
)
set(GAME_CODE 
    ${GAME_DIR}material/phong_spot.cpp
    ${GAME_DIR}material/blinn_phong_point.cpp
    ${GAME_DIR}material/function_chart.cpp
    ${GAME_DIR}logic/function_draw.cpp
    ${GAME_DIR}logic/camera_logic.cpp
)

set(EXAMPLE_CODE
    ${EXAMPLE_DIR}function_chart/main.cpp
    ${EXAMPLE_DIR}protobuf_test/main.cpp
)

add_compile_options(-Wno-unused-function)
add_library(src 
    ${COMM_CODE}
    ${all_srcs} 
    )
target_include_directories(src PUBLIC ${INCLUDE_DIR})
