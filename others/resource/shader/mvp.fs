#version 330 core

out vec4 FragColor;

in vec2 u_UV;
in vec3 u_Normal;
in vec3 u_FragPos;

uniform sampler2D ourTexture;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
    // ambient light
    float ambientFactor = 0.1;
    vec3 light_ambient = ambientFactor * lightColor;
    // diffuse light
    vec3 norm = normalize(u_Normal);
    vec3 lightDir = normalize(lightPos - u_FragPos);
    float diffFactor = max(dot(norm, lightDir), 0.0);
    vec3 light_diffuse = diffFactor * lightColor;
    // specular light
    vec3 viewDir = normalize(viewPos - u_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 light_spec = 0.5 * spec * lightColor;
    // combination light -> Phone
    vec4 object_color = texture(ourTexture, u_UV);
    //
    FragColor = vec4((light_ambient + light_diffuse + light_spec) * object_color.rgb, object_color.a);
}
