
out vec4 FragColor;

layout (location = 2) in vec2 vUV;


uniform sampler2D depthMap;

uniform int isPerspective;
uniform float near_plane;
uniform float far_plane;


// required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main()
{
    if(isPerspective == 1)
    {
        float depthValue = texture(depthMap, vUV).r;
        FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
        
    }
    else
    {
        float depthValue = texture(depthMap, vUV).r;
        FragColor = vec4(vec3(depthValue), 1.0); // orthographic
    }





    
}