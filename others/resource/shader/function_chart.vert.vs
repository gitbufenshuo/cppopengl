#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 uni_Model;
uniform mat4 uni_View;
uniform mat4 uni_Proj;

out float io_tou_x;

void main() {
    mat4 mvp = uni_Proj * uni_View * uni_Model;
    vec4 tou = mvp * vec4(aPos.x, 0.0f, -aPos.y, 1.0);
    io_tou_x = tou.x / tou.w;
    gl_Position = tou;
}
