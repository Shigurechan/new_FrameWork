#version 420

out vec4 fragment;

layout(location = 3) in vec4 Color; // ピクセルシェーダに渡す色

void main()
{
    fragment = Color;
}