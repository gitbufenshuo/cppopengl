set (MC_LOW_DIR mc/low/)
set (LOW_CODE 
${MC_LOW_DIR}transform.cpp 
${MC_LOW_DIR}shader.cpp 
${MC_LOW_DIR}camera.cpp 
${MC_LOW_DIR}model.cpp 
${MC_LOW_DIR}texture.cpp 
${MC_LOW_DIR}material_phong.cpp 
${MC_LOW_DIR}engine.cpp 
${MC_LOW_DIR}mesh_render.cpp
${MC_LOW_DIR}gameobject.cpp
${MC_LOW_DIR}logic_support.cpp
${MC_LOW_DIR}shader_store.cpp
${MC_LOW_DIR}model_store.cpp
${MC_LOW_DIR}texture_store.cpp
${MC_LOW_DIR}material_store.cpp
)
set (TOOLS_CODE tools_image.cpp)
set (APPS_CODE app.cpp apps_init.cpp apps_vao.cpp apps_xyzw.cpp apps_math.cpp apps_csv.cpp apps_camera.cpp)

add_compile_options(-Wno-unused-function)
add_library(src ${APPS_CODE} ${LOW_CODE} ${TOOLS_CODE})
target_include_directories(src PUBLIC ${INCLUDE_DIR})