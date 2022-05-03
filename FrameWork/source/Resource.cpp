#include "../header/Resource.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include <sys/timeb.h> 
#include <stdio.h>
#include <random>

#include <stb/stb_image.h>
//#include <sys/timeb.h> 

// ##################################### シェーダーをロード ##################################### 
std::shared_ptr<std::vector<GLchar>> FrameWork::LoadShader(const char* fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (file.fail() == true)
    {
        std::cerr << "シェーダーファイルを読み込めません: " << fileName << std::endl;
        file.close();
    }
    else
    {	
        std::shared_ptr<std::vector<GLchar>> buffer = std::make_shared<std::vector<GLchar>>();
        file.seekg(0L, std::ios::end);
        GLsizei length = static_cast<GLsizei>(file.tellg());
        buffer->resize(length + 1);
        file.seekg(0L, std::ios::beg);
        file.read(buffer->data(), length);
        buffer->at(length) = ('\0');

        file.close();

        return buffer;      
    }

    file.close();  
    
    return nullptr;
}

// ##################################### テクスチャをロード ##################################### 
FrameWork::Texture FrameWork::LoadTexture(const char* fileName)
{
    Texture texture;

    glm::ivec2 size;
    int channel;

    unsigned char* data = NULL;
    data = stbi_load(fileName, &size.x, &size.y, &channel, 0);
    texture.size = size;

    if (data == NULL)
    {
        std::cerr << "画像が見つかりません: " << fileName << std::endl;
        assert(0);
    }

    glGenTextures(1, &texture.ID);            //テクスチャIDの生成
    glBindTexture(GL_TEXTURE_2D, texture.ID); // IDバインド

    //テクスチャ生成

    if (channel == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else if (channel == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (channel == 2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, size.x, size.y, 0, GL_RG, GL_UNSIGNED_BYTE, data);
    }
    else if (channel == 1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cerr << "未対応の形式のチャンネル数です: " << fileName <<"    "<< "チャンネル数: "<<channel<< std::endl;
        assert(0);
    }

    // テクスチャの補間設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    texture.data = data;



    stbi_image_free(texture.data);
    return texture;

}

// ##################################### テクスチャを削除 ##################################### 
void FrameWork::DeleteTexture(FrameWork::Texture texture)
{
    glDeleteTextures(1,&texture.ID);
    //stbi_image_free(texture.data);
    texture.data = NULL;
}

// ##################################### 乱数　取得 ##################################### 
int FrameWork::GetRandom(int start, int end)
{
	std::random_device rnd;                             // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());                             //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> Rand(start, end);   // [start, end] 範囲の一様乱数	

	return Rand(mt);
}
