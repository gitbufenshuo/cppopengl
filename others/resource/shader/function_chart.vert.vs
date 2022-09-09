#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 uni_Model;
uniform mat4 uni_View;
uniform mat4 uni_Proj;

out vec3 io_color;
out float io_height;

void main() {
    mat4 mvp = uni_Proj * uni_View * uni_Model;
    vec2 good_v_coord = aPos * 0.02 * 3.14 * 2.0;
    float height = sin(good_v_coord.x);
    vec4 tou = mvp * vec4(good_v_coord.x, height, good_v_coord.y, 1.0);
    gl_Position = tou;
    io_height = (height + 1.0) * 0.5;
    if((gl_VertexID / 6) % 2 == 0) {
        io_color = vec3(0.2, 0.2, 0.2);
    } else {
        io_color = vec3(0.8, 0.8, 0.8);
    }
}
