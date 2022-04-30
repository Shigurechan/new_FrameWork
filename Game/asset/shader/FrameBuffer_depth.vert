#version 420


layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 vertexUV;

layout (location = 2) out vec2 vUV;

void main()
{
    vUV = vertexUV;

    gl_Position = vec4(vertexPosition.x,vertexPosition.y,-1.0,1.0); 
}  