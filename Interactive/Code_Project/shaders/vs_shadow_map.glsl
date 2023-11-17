// This code is based on https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping

#version 410 core

layout (location = 0) in vec3 in_vertex;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 lightSpace_matrix;

void main()
{   
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(in_vertex, 1.0);
    vs_out.TexCoords = in_texCoords;

    vs_out.Normal = transpose(inverse(mat3(model_matrix))) * in_normal;

    vs_out.FragPos = vec3(model_matrix * vec4(in_vertex, 1.0));
    
    vs_out.FragPosLightSpace = lightSpace_matrix * vec4(vs_out.FragPos, 1.0);
    
}