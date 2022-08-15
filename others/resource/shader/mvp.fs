#version 330 core
out vec4 FragColor;
in vec2 u_UV;
void main() {
    FragColor = vec4(u_UV, 1.0f, 1.0f);
}
