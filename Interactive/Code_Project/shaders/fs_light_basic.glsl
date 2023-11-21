#version 410 core

out vec4 color;

in VS_OUT
{
    vec3 vertex;
    vec3 normals;
    vec2 tc;
} fs_in;

uniform sampler2D tex;
uniform mat4 model_matrix;

uniform float brightness;

void main(void){
  //color = brightness * texture(tex, fs_in.tc);
  color = texture(tex, fs_in.tc);
}
