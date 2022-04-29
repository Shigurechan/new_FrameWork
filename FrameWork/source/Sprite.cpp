#include "../header/Sprite.hpp"

#include <array>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../header/Resource.hpp"
#include "../header/Window.hpp"
#include "../header/Init.hpp"
#include "../header/Sprite_Use.hpp"

// ##################################### テクスチャ描画　公開 ##################################### 
void FrameWork::RenderGraph(const glm::mat4 view,const glm::vec3 position,const FrameWork::Texture texture)
{
	FrameWork::sprite->Render(view,position,texture);
}

// ##################################### テクスチャ描画 サイズ　公開 ##################################### 
void FrameWork::RenderGraph_Size(const glm::mat4 view,const glm::vec3 position,const FrameWork::Texture texture,glm::vec2 startSize,glm::vec2 endSize)
{
	FrameWork::sprite->Render_Size(view,position,texture,startSize,endSize);
}


// ##################################### コンストラクタ ##################################### 
FrameWork::Sprite::Sprite() : FrameWork::Transform()
{
	vao = 0;
	vbo = 0;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	
    shader = std::make_unique<Shader>();
	shader->Load("asset/shader/2D/BasicTexture_2D.vert","asset/shader/2D/BasicTexture_2D.frag");

	shader->setEnable();

	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexAttribute), (float*)vertex.data(), GL_DYNAMIC_DRAW);

	GLuint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, (sizeof(VertexAttribute) / sizeof(float)) * sizeof(float), (GLvoid*)(sizeof(GLfloat) * 0));
	shader->setBindAttribLocation("vertexPosition");

	attrib = shader->getAttribLocation("vertexUV");
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, (sizeof(VertexAttribute) / sizeof(float)) * sizeof(float), (GLvoid*)(sizeof(GLfloat) * 3));
	shader->setBindAttribLocation("vertexUV");

	shader->setDisable();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

// ##################################### テクスチャ描画 ##################################### 
void FrameWork::Sprite::Render(const glm::mat4 view,const glm::vec3 position,const FrameWork::Texture texture)
{
    shader->setEnable();
	glm::vec2 screenSize = glm::vec2(1.0f / FrameWork::currentWindow->getSize().x,1.0f / FrameWork::currentWindow->getSize().y);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	setSize(glm::ivec2(0,0),texture.size);
	setUV(glm::ivec2(0,0),texture.size,texture.size);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex.size(), vertex.data());

	Transform::setPosition(position);
	//Transform::setPosition(glm::vec3(position.x,position.y,0));
	Transform::setRotate(glm::vec3(0, 0, 1), 0);
	Transform::setScale(glm::vec3(texture.size,1));

	shader->setUniformSampler2D("uImage",0,texture.ID);
	shader->setUniformMatrix4fv("uTranslate", Transform::getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", Transform::getMatRotate());
	shader->setUniformMatrix4fv("uScale", Transform::getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", view);

	glDrawArrays(GL_TRIANGLES,0,vertex.size());
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	shader->setDisable();
}


// ##################################### テクスチャ描画 サイズ指定 ##################################### 
void FrameWork::Sprite::Render_Size(const glm::mat4 view,const glm::vec3 position,const FrameWork::Texture texture,glm::vec2 startSize,glm::vec2 endSize)
{
    shader->setEnable();
	glm::vec2 screenSize = glm::vec2(1.0f / FrameWork::currentWindow->getSize().x,1.0f / FrameWork::currentWindow->getSize().y);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	setSize(startSize,endSize);
	setUV(startSize,endSize,texture.size);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex.size(), vertex.data());




	Transform::setPosition(position);
	//Transform::setPosition(glm::vec3(position.x,position.y,0));
	Transform::setRotate(glm::vec3(0, 0, 1), 0);
	Transform::setScale(glm::vec3(endSize - startSize,1));

	shader->setUniformSampler2D("uImage",0,texture.ID);
	shader->setUniformMatrix4fv("uTranslate", Transform::getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", Transform::getMatRotate());
	shader->setUniformMatrix4fv("uScale", Transform::getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", view);

	glDrawArrays(GL_TRIANGLES,0,vertex.size());
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	shader->setDisable();
}





// ##################################### 頂点 #####################################
void FrameWork::Sprite::setSize(const glm::vec2 startSize,const glm::vec2 endSize)
{

	glm::vec2 scr = glm::ivec2(1,1);
	scr.x = 1.0f/ 2.0f;
	scr.y = 1.0f/ 2.0f;

	// 頂点座標
	vertex[0].position.x = -scr.x;
	vertex[0].position.y = scr.y;
	vertex[0].position.z = 0;

	vertex[1].position.x = -scr.x;
	vertex[1].position.y = -scr.y;
	vertex[1].position.z = 0;

	vertex[2].position.x = scr.x;
	vertex[2].position.y = scr.y;
	vertex[2].position.z = 0;

	vertex[3].position.x = scr.x;
	vertex[3].position.y = scr.y;
	vertex[3].position.z = 0;

	vertex[4].position.x = -scr.x;
	vertex[4].position.y = -scr.y;
	vertex[4].position.z = 0;

	vertex[5].position.x = scr.x;
	vertex[5].position.y = -scr.y;
	vertex[5].position.z = 0;


}




// ##################################### 頂点 #####################################
void FrameWork::Sprite::setUV(const glm::vec2 startSize, const glm::vec2 endSize,const glm::ivec2 textureSize)
{
	glm::vec2 size = endSize - startSize;


	//UV座標
	float sizeX = 1.0f / (float)textureSize.x;
	float sizeY = 1.0f / (float)textureSize.y;

	FrameWork::Sprite::vertex[0].uv.x = sizeX * startSize.x;
	FrameWork::Sprite::vertex[0].uv.y = sizeY * startSize.y;

	FrameWork::Sprite::vertex[1].uv.x = sizeX * startSize.x;
	FrameWork::Sprite::vertex[1].uv.y = sizeY * endSize.y;

	FrameWork::Sprite::vertex[2].uv.x = sizeX * endSize.x;
	FrameWork::Sprite::vertex[2].uv.y = sizeY * startSize.y;

	FrameWork::Sprite::vertex[3].uv.x = sizeX * endSize.x;
	FrameWork::Sprite::vertex[3].uv.y = sizeY * startSize.y;

	FrameWork::Sprite::vertex[4].uv.x = sizeX * startSize.x;
	FrameWork::Sprite::vertex[4].uv.y = sizeY * endSize.y;

	FrameWork::Sprite::vertex[5].uv.x = sizeX * endSize.x;
	FrameWork::Sprite::vertex[5].uv.y = sizeY * endSize.y;
}


FrameWork::Sprite::~Sprite()
{

}