#version 330 core

out vec4 FragColor;

in vec2 u_UV;

uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, u_UV);
}
