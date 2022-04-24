#ifndef ___SPRITE_2D_HPP_
#define ___SPRITE_2D_HPP_

#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../header/GameObject.hpp"
#include "../header/Resource.hpp"
#include "../header/Shader.hpp"
#include "../header/Transform.hpp"

/*#########################################################################
# スプライトクラス
説明
	2Dのテクスチャ描画　正射形
###########################################################################*/

/*#########################################################################
*NOTE 
* 
* 頂点の順番
* 0	      2,3
* 1,4		5
###########################################################################*/


namespace FrameWork
{	
	class Sprite : FrameWork::Transform
	{
	public:

		Sprite();
		~Sprite();

        void Render(const glm::mat4 view,const glm::vec3 position,const FrameWork::Texture texture);
        void Render_Size(const glm::mat4 view,const FrameWork::Texture texture,const glm::vec3 position,const glm::ivec2 startSize,const glm::ivec2 endSize);

        std::unique_ptr<Shader> shader;
	private:

		GLuint vao;
		GLuint vbo;

		std::array<VertexAttribute, 6> vertex;


        void setUV(const glm::vec2 startSize, const glm::vec2 endSize,const glm::ivec2 textureSize);
        void setSize(const glm::vec2 startSize,const glm::vec2 endSize);
	};
}
#endif