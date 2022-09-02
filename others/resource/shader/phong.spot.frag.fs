#version 330 core
out vec4 FragColor;

struct Material {
    vec3 specular;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 io_UV;
in vec3 io_Normal;
in vec3 io_FragPos;

uniform vec3 uni_viewPos;
uniform SpotLight uni_spotLight;
uniform Material uni_material;
uniform sampler2D uni_ourTexture;

// function prototypes
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {    
    // properties
    vec3 norm = normalize(io_Normal);
    vec3 viewDir = normalize(uni_viewPos - io_FragPos);

    // spot light
    vec3 result = CalcSpotLight(uni_spotLight, norm, io_FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff_factor = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec_factor = pow(max(dot(viewDir, reflectDir), 0.0), uni_material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 sample_color = vec3(texture(uni_ourTexture, io_UV));
    vec3 ambient_diffuse = (light.ambient + light.diffuse * diff_factor) * sample_color;
    vec3 specular = light.specular * spec_factor * uni_material.specular;
    // return vec3(intensity, intensity, intensity);
    return (ambient_diffuse + specular) * attenuation * intensity;
}