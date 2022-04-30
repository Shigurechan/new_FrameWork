
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 vertexUV;

layout (location = 2) out vec2 TexCoords;

void main()
{
    TexCoords = vertexUV;
    gl_Position = vec4(vertexPosition.x,vertexPosition.y,0.0,1.0);
}