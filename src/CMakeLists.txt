set (LOW_CODE 
low_transform.cpp 
low_shader.cpp 
low_camera.cpp 
low_model.cpp 
low_texture.cpp 
low_material.cpp 
low_engine.cpp 
low_mesh_render.cpp
low_gameobject.cpp
)
set (TOOLS_CODE tools_image.cpp)
set (APPS_CODE app.cpp apps_init.cpp apps_vao.cpp apps_xyzw.cpp apps_math.cpp apps_csv.cpp apps_camera.cpp)

add_compile_options(-Wno-unused-function)
add_library(src ${APPS_CODE} ${LOW_CODE} ${TOOLS_CODE})
target_include_directories(src PUBLIC ${INCLUDE_DIR})