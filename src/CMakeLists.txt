set (MC_LOW_DIR mc/low/)
set(GAME_DIR game/)
set(EXAMPLE_DIR example/)
set(MC_COMM_DIR mc/comm/)
set(MC_GLTF_DIR mc/gltf/)
set(MC_ASSET_DIR mc/asset/)

file(GLOB_RECURSE LOW_CODE ${MC_LOW_DIR}*.cpp)

file(GLOB_RECURSE COMM_CODE ${MC_COMM_DIR}*.cc)

file(GLOB_RECURSE MC_GLTF_CODE ${MC_GLTF_DIR}*.cpp)

set (TOOLS_CODE tools_image.cpp)

file(GLOB_RECURSE GAME_CODE ${GAME_DIR}*.cpp)

file(GLOB_RECURSE EXAMPLE_CODE ${EXAMPLE_DIR}*.cpp)

file(GLOB_RECURSE ASSET_CODE ${MC_ASSET_DIR}*.cpp)


add_compile_options(-Wno-unused-function)
add_library(src 
    ${LOW_CODE}
    ${COMM_CODE} 
    ${MC_GLTF_CODE}
    ${TOOLS_CODE}
    ${GAME_CODE}
    ${EXAMPLE_CODE}
    ${ASSET_CODE}
)
target_include_directories(src PUBLIC ${INCLUDE_DIR})
