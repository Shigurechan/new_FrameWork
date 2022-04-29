#version 420

layout(location = 0) in vec3 vertexPosition;	
layout(location = 1) in vec2 vertexUV;	
layout(location = 2) in vec3 vertexNormal;	

layout(location = 3) out vec2 TexCoords;
layout(location = 4) out vec3 WorldPos;
layout(location = 5) out vec3 Normal;

uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		
uniform mat4 uViewProjection;	

void main()
{
	mat4 model = uTranslate * uRotate * uScale;		


    TexCoords = vertexUV;
    WorldPos = vec3(model * vec4(vertexPosition, 1.0));
    Normal = mat3(model) * vertexNormal;   


    gl_Position = (uViewProjection * model) * vec4(vertexPosition,1.0);

}

