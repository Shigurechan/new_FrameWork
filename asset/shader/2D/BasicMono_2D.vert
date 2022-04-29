/*#########################################################################
# 単色の二次元描画　頂点シェーダー 
###########################################################################*/
<<<<<<< HEAD


=======
>>>>>>> 3e76fcf6a7b11b57e737573b25a4f1f0a3382b34
#version 140
#extension GL_ARB_separate_shader_objects: enable
#extension GL_ARB_explicit_attrib_location: enable

//#extension GL_ARB_explicit_uniform_location : require

// ######################  ###################### 
layout(location = 0) in vec2 vertexPosition;	//

// ######################  ###################### 
layout(location = 2) out vec4 vFragment;	//

// ###################### Uniform ###################### 
uniform mat4 uScale;			//
uniform mat4 uRotate;			//
uniform mat4 uTranslate;		//
uniform mat4 uViewProjection;		//
uniform vec4 uFragment;			//


void main()
{
	vec4 vertex = vec4(vertexPosition,0.0,1.0);		//
	mat4 model = uTranslate * uRotate * uScale;		//

	gl_Position =  (uViewProjection * model) * vertex;
	
	vFragment = uFragment;				//
}