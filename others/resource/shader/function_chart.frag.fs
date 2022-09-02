#version 330 core

out vec4 FragColor;

in float io_tou_x;

void main() {

    FragColor = vec4(io_tou_x + 0.5, io_tou_x, io_tou_x, 1.0f);
}
