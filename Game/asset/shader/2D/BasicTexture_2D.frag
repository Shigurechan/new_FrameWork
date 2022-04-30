/*#########################################################################
#  
###########################################################################*/
#version 140
#extension GL_ARB_separate_shader_objects: enable
#extension GL_ARB_explicit_attrib_location: enable


// ######################  ###################### 
layout(location = 2) in vec2 vUV;	

// ###################### Unifrom ###################### 
uniform sampler2D uImage;		
		

out vec4 fragment;

void main()
{
	fragment = texture(uImage,vUV);
}