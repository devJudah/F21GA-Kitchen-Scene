// Basic shader to use for stencil testing. Can probably be even simplier
// Just a copy of vs_model
#version 410 core

layout (location = 0) in vec3 in_vertex;
layout (location = 1) in vec3 in_normals;
layout (location = 2) in vec2 in_tc;

out vec2 TexCoords;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

uniform float outlineSize;

void main(void)
{

    // Basic - Scale the model itself before passing it in
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(in_vertex, 1.0);

    // Scale model
    // gl_Position = proj_matrix * view_matrix * model_matrix * outlineSize * vec4(in_vertex, 1.0);

    // Alternative method using normals to scale
    // gl_Position = proj_matrix * view_matrix * model_matrix * vec4(in_vertex + in_normals * outlineSize, 1.0);

    TexCoords = in_tc;
}
