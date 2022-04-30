#version 330 core
layout (location = 0) in vec3 vertexPosition;

uniform mat4 lightSpaceMatrix;

uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		


void main()
{

    vec4 vertex = vec4(vertexPosition,1.0);
    mat4 model = uTranslate * uRotate * uScale;		
    gl_Position = (lightSpaceMatrix * model) * vertex;


  //gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
      //mat4 model = uTranslate * uRotate * uScale;		
    //gl_Position = lightSpaceMatrix * model * vec4(vertexPosition, 1.0);
}