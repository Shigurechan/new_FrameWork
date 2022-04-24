#include "../header/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

// ##################################### コンストラクタ ##################################### 
FrameWork::Transform::Transform()
{
        matScale = glm::mat4(0);			//拡大縮小
        matRotate  = glm::mat4(0);		    //回転
        matTranslation  = glm::mat4(0);	    //平行移動    
}

// ##################################### 座標　設定 ##################################### 
void FrameWork::Transform::setPosition(const glm::vec3 p)
{
	matTranslation = glm::translate(glm::mat4(1), glm::vec3(p.x, p.y,p.z));
}

// ##################################### スケール　設定 ##################################### 
void FrameWork::Transform::setScale(const glm::vec3 s)
{
	matScale = glm::scale(glm::mat4(1), glm::vec3(s.x, s.y, s.z));
}

// ##################################### 回転　設定 ##################################### 
void FrameWork::Transform::setRotate(const glm::vec3 vec,float r)
{
	matRotate = glm::rotate(glm::mat4(1),r, vec);
}

/* ############################################################### 行列　取得 ###############################################################  */

// ##################################### 平行移動　行列　取得 ##################################### 
glm::mat4 FrameWork::Transform::getMatTranslation()
{
	return matTranslation;
}

// ##################################### スケール　行列　取得 ##################################### 
glm::mat4 FrameWork::Transform::getMatScale()
{
	return matScale;
}

// ##################################### 回転　行列　取得 ##################################### 
glm::mat4 FrameWork::Transform::getMatRotate()
{
	return matRotate;
}

/* ############################################################### 行列　設定 ###############################################################  */

// ##################################### 平行移動　行列 ##################################### 
void FrameWork::Transform::setMatTranslation(const glm::mat4 mat)
{
	matTranslation = mat;
}

// ##################################### スケール　行列 ##################################### 
void FrameWork::Transform::setMatScale(const glm::mat4 mat)
{
	matScale = mat;
}

// ##################################### 回転　行列　 ##################################### 
void FrameWork::Transform::setMatRotate(const glm::mat4 mat)
{
	matRotate = mat;
}

// ##################################### デストラクタ ##################################### 
FrameWork::Transform::~Transform()
{

}
