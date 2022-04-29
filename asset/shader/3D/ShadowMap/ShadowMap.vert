
#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;


uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		

uniform mat4 uViewProjection;	
uniform mat4 lightSpaceMatrix;

void main()
{
      vec4 vertex = vec4(vertexPosition,1.0);
      mat4 model = uTranslate * uRotate * uScale;		
      gl_Position = (uViewProjection * model) * vertex;
	
      vs_out.FragPos = vec3(model * vec4(vertexPosition, 1.0));
      vs_out.Normal = transpose(inverse(mat3(model))) * vertexNormal;
      vs_out.TexCoords = vertexUV;
      vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);





}