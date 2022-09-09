#version 330 core

out vec4 FragColor;

in vec3 io_color;
in float io_height;

void main() {
    FragColor = vec4(io_color, 1.0f);
}
