#version 420

//layout (location = 0) out vec4 FragColor;
layout (location = 0) out vec4 fragColor;


uniform sampler2D tex;

layout(location = 2) in vec2 vUV; //UV

void main() 
{
    
    fragColor = texture(tex, vUV);


}