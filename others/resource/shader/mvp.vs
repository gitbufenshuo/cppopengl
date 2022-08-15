#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;

out vec2 u_UV;

uniform mat4 ma_Model;
uniform mat4 ma_View;
uniform mat4 ma_Proj;

void main() {
    u_UV = aUV;
    mat4 mvp = ma_Proj * ma_View * ma_Model;
    gl_Position = mvp * vec4(aPos, 1.0f);
    // gl_Position = vec4(aPos, 1.0f);
}
