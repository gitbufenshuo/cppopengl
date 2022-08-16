#version 330 core

out vec4 FragColor;

in vec2 u_UV;
in vec3 u_Normal;
in vec3 u_FragPos;

uniform sampler2D ourTexture;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
    float ambientStrength = 0.1;
    vec3 light_ambient = ambientStrength * lightColor;

    vec3 norm = normalize(u_Normal);
    vec3 lightDir = normalize(lightPos - u_FragPos);
    float diffFactor = max(dot(norm, lightDir), 0.0) * 0.5;
    vec3 light_diffuse = diffFactor * lightColor;
    // light_diffuse = vec3(0.0, 0.0, 0.0);
    vec4 object_color = texture(ourTexture, u_UV);
    FragColor = vec4((light_ambient + light_diffuse) * object_color.rgb, object_color.a);
}
