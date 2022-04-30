/*#########################################################################
# 単色の二次元描画　フラグメントシェーダー
###########################################################################*/
<<<<<<< HEAD

=======
>>>>>>> 3e76fcf6a7b11b57e737573b25a4f1f0a3382b34
#version 140
#extension GL_ARB_separate_shader_objects: enable
#extension GL_ARB_explicit_attrib_location: enable


//#extension GL_ARB_explicit_uniform_location : require

// ###################### 入力 ###################### 
layout(location = 2) in vec4 vfragment;	//カラー

// ###################### 出力 ###################### 
out vec4 fragment;

void main()
{
	fragment = vfragment;
}