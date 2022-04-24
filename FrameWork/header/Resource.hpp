#ifndef ___RESOURCE_HPP_
#define ___RESOURCE_HPP_

#include <vector>
#include <iostream>
#include <fstream>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace FrameWork
{
    struct VertexAttribute
	{
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec4 color;

	};




    //テクスチャ
    typedef struct texture
    {
        glm::ivec2 size = glm::ivec2(0,0);    //サイズ
        GLuint ID = 0;                        //ID
        unsigned char* data;                  //データ
    }
    Texture;



    std::shared_ptr<std::vector<GLchar>> LoadShader(const char* fileName);                                       //シェーダー読み込み
    Texture LoadTexture(const char* fileName);                //テクスチャ読み込み


}

#endif