
layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec2 vertexUV;
layout (location = 1) in vec3 vertexNormal;
layout (location = 3) in vec3 vertexTangent;
//layout (location = 4) in vec3 vertexBinormal;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		
uniform mat4 uViewProjection;	



uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec4 vertex = vec4(vertexPosition,1.0);
    mat4 model = uTranslate * uRotate * uScale;		
    gl_Position = (uViewProjection * model) * vertex;

    vs_out.FragPos = vec3(model * vec4(vertexPosition, 1.0));   
    vs_out.TexCoords = vertexUV;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * vertexTangent);
    vec3 N = normalize(normalMatrix * vertexNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
        
//    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}