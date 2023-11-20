// Just output a single colour

#version 410 core

out vec4 FragColor;

uniform vec4 singleColor;

void main(){

  FragColor = singleColor;

}