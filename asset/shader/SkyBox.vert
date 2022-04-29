#version 420

layout (location = 0) in vec3 vertexPosition;

layout (location = 1) out vec3 TexCoords;

uniform mat4 uViewProjection;	

void main()
{
	TexCoords = vertexPosition;
//    TexCoords = normalize(vertexPosition);
    vec4 pos = uViewProjection * vec4(vertexPosition, 1.0);

    gl_Position = pos.xyww;
}  

