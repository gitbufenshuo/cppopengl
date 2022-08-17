#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out vec2 io_UV;
out vec3 io_Normal;
out vec3 io_FragPos;

uniform mat4 ma_Model;
uniform mat4 ma_View;
uniform mat4 ma_Proj;

void main() {
    io_UV = aUV;
    io_Normal = vec3(ma_Model * vec4(aNormal, 0.0));
    io_FragPos = vec3(ma_Model * vec4(aPos, 1.0));

    mat4 mvp = ma_Proj * ma_View * ma_Model;
    gl_Position = mvp * vec4(aPos, 1.0);
}
