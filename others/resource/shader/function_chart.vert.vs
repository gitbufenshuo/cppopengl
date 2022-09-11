#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 uni_Model;
uniform mat4 uni_View;
uniform mat4 uni_Proj;

out vec3 io_color;

void main() {
    mat4 mvp = uni_Proj * uni_View * uni_Model;
    vec2 good_v_coord = aPos * 0.2;
    vec4 tou = mvp * vec4(good_v_coord.x, good_v_coord.y, -10.0, 1.0);
    gl_Position = tou;
    io_color = aColor;
}
