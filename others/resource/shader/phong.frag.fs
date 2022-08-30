#version 330 core

out vec4 FragColor;

in vec2 io_UV;
in vec3 io_Normal;
in vec3 io_FragPos;

uniform sampler2D ourTexture;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
    // ambient light
    vec3 light_ambient = material.ambient * lightColor;
    // diffuse light
    vec3 norm = normalize(io_Normal);
    vec3 lightDir = normalize(lightPos - io_FragPos);
    float diffFactor = max(dot(norm, lightDir), 0.0);
    vec3 light_diffuse = diffFactor * material.diffuse * lightColor;
    // specular light
    vec3 viewDir = normalize(viewPos - io_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 light_spec = specFactor * material.specular * lightColor;
    // combination light -> Phone
    vec4 object_color = texture(ourTexture, io_UV);
    //
    vec3 ocolor = (light_ambient + light_diffuse + light_spec) * object_color.rgb;

    FragColor = vec4(ocolor, object_color.a);
}
