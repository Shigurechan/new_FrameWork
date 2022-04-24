#version 330 core
layout (location = 0) in vec3 vertexPosition;

// ###################### Uniform ###################### 
uniform mat4 uScale;		
uniform mat4 uRotate;		
uniform mat4 uTranslate;	


uniform mat4 lightSpaceMatrix;


void main()
{
	mat4 model = uTranslate * uRotate * uScale;		

    gl_Position = lightSpaceMatrix * model * vec4(vertexPosition, 1.0);
}