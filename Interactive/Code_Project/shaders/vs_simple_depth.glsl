// This code is based on - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping

#version 410 core

layout (location = 0) in vec3 aPos;

uniform mat4 model_matrix;
uniform mat4 lightSpace_matrix;

void main()
{   
    // lightSpace_matrix = lightView_matrix * lightProj_matrix
    gl_Position = lightSpace_matrix * model_matrix * vec4(aPos, 1.0);
}