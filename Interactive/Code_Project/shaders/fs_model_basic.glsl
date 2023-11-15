#version 410 core

out vec4 color;

in VS_OUT
{
    vec4 fragPos;
    vec4 normals;
    vec2 tc;
} fs_in;

uniform sampler2D tex;
uniform mat4 model_matrix;

uniform vec4 lightPosition;
uniform vec4 viewPosition;

uniform float k_ambient;        // Ambient constant
uniform vec4 color_ambient;     // Ambient colour
uniform float k_diffuse;        // Diffuse constant
uniform vec4 color_diffuse;     // diffuse colour
uniform float k_specular;       // specular constant
uniform vec4 color_specular;    // specular colour
uniform float shininess;        // shininess constant

// See Table in Lecture 14 - Advanced lightning for possible values
uniform float atten_constant;   // Attenuation constant
uniform float atten_linear;     // Attenuation linear term
uniform float atten_quadratic;  // Attenuation quadratic term


void main(void){

    // Ambient
    vec3 ambient = k_ambient * color_ambient.rgb;

    // Diffuse
    vec4 lightDir = normalize(lightPosition - fs_in.fragPos);
    float diff = max(dot(normalize(fs_in.normals), lightDir), 0.0);
    vec3 diffuse = k_diffuse * color_diffuse.rgb * diff;

    // Specular
    vec4 viewDir = normalize(viewPosition - fs_in.fragPos);
    vec4 reflectDir = reflect(-lightDir, normalize(fs_in.normals));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = k_specular * color_specular.rgb * spec;

    // Attenuation
    float distance = length(lightPosition - fs_in.fragPos);
    float attenuation = 1.0f / (atten_constant + atten_linear * distance + atten_quadratic * (distance * distance));

    // Adjust values based on attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Overall Light
    color = vec4(ambient + diffuse + specular, 1.0) * texture(tex, fs_in.tc);
}
