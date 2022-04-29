#version 330 core

layout(location = 0) in vec2 vertexPosition;	


uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		
uniform mat4 uViewProjection;	

void main()
{
	mat4 model = uTranslate * uRotate * uScale;		

    gl_Position = (uViewProjection * model) * vec4(vertexPosition,-1.0, 1.0);
}