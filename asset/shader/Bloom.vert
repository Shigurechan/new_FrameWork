


layout(location = 0) in vec3 vertexPosition;	
layout(location = 1) in vec2 vertexUV;	
layout(location = 2) in vec3 vertexNormal;	

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		
uniform mat4 uViewProjection;	

void main()
{
	mat4 model = uTranslate * uRotate * uScale;		

    vs_out.FragPos = vec3(model * vec4(vertexPosition, 1.0));   
    vs_out.TexCoords = vertexUV;
        
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vs_out.Normal = normalize(normalMatrix * vertexNormal);
    

    gl_Position = (uViewProjection * model) * vec4(vertexPosition,1.0);

}

