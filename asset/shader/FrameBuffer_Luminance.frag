#version 140
#extension GL_ARB_separate_shader_objects: enable
#extension GL_ARB_explicit_attrib_location: enable

//layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


uniform sampler2D tex;
//uniform float minBright;

layout(location = 2) in vec2 vUV; //UV

void main() 
{
    //vec3 texel = max(vec3(0.0), (texture(tex, vUV) - 0.5).rgb);
    vec3 texel = max(vec3(0.0), (texture(tex, vUV) - 0.5).rgb);
    
    //FragColor = vec4(texel, 1.0);
    BrightColor = vec4(texel, 1.0);
    //BrightColor = vec4(0.0,1.0,0.0, 1.0);

}