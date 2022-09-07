set (MC_LOW_DIR mc/low/)
set(GAME_DIR game/)
set(EXAMPLE_DIR example/)
set(MC_COMM_DIR mc/comm/)
set(MC_GLTF_DIR mc/gltf/)

set (LOW_CODE 
    ${MC_LOW_DIR}transform.cpp
    ${MC_LOW_DIR}shader.cpp
    ${MC_LOW_DIR}camera.cpp
    ${MC_LOW_DIR}model.cpp
    ${MC_LOW_DIR}texture.cpp
    ${MC_LOW_DIR}material_phong.cpp
    ${MC_LOW_DIR}engine.cpp
    ${MC_LOW_DIR}engine_cursor.cpp
    ${MC_LOW_DIR}engine_keyinput.cpp
    ${MC_LOW_DIR}keyinputsystem.cpp
    ${MC_LOW_DIR}mesh_render.cpp
    ${MC_LOW_DIR}gameobject.cpp
    ${MC_LOW_DIR}logic_support.cpp
    ${MC_LOW_DIR}shader_store.cpp
    ${MC_LOW_DIR}model_store.cpp
    ${MC_LOW_DIR}texture_store.cpp
    ${MC_LOW_DIR}material_store.cpp
)
set (COMM_CODE 
    ${MC_COMM_DIR}transform.pb.cc
    ${MC_COMM_DIR}gltf.pb.cc
)

set (MC_GLTF_CODE
    ${MC_GLTF_DIR}buffer.cpp
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
    ${EXAMPLE_DIR}gltf_exp/main.cpp
)

add_compile_options(-Wno-unused-function)
add_library(src 
    ${APPS_CODE} 
    ${LOW_CODE} 
    ${TOOLS_CODE} 
    ${GAME_CODE} 
    ${EXAMPLE_CODE}
    ${COMM_CODE}
    ${MC_GLTF_CODE}
    )
target_include_directories(src PUBLIC ${INCLUDE_DIR})
