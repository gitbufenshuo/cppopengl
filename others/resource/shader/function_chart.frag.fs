#version 330 core

out vec4 FragColor;

in vec3 io_color;
in float io_height;

void main() {
    FragColor = vec4(io_height, io_height, io_height, 1.0f);
}
