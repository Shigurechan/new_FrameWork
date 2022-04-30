
#version 140
#extension GL_ARB_separate_shader_objects: enable
#extension GL_ARB_explicit_attrib_location: enable

out vec4 fragment;

  
layout (location = 2) in vec2 UV;

uniform sampler2D screenTexture;

void main()
{ 
    
    fragment = texture(screenTexture, UV);
}