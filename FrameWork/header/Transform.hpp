#ifndef ___TRANSFORM_HPP_
#define ___TRANSFORM_HPP_

#include <glm/glm.hpp>

/*#########################################################################
# Transformクラス

説明

###########################################################################*/


namespace FrameWork
{
    class Transform
    {
    public:
        Transform();                                    //コンストラクタ
        ~Transform();                                   //デストラクタ

        void setPosition(const glm::vec3 p);			//座標
        void setScale(const glm::vec3 s);				//スケール
        void setRotate(const glm::vec3 vec,float r);	//回転
            
        glm::mat4 getMatTranslation();	//座標
        glm::mat4 getMatScale();		//スケール
        glm::mat4 getMatRotate();		//回転
            
        void setMatTranslation(const glm::mat4 mat);	//座標
        void setMatScale(const glm::mat4 mat);			//スケール
        void setMatRotate(const glm::mat4 mat);			//回転

    private:

        //行列
        glm::mat4 matScale;			//拡大縮小
        glm::mat4 matRotate;		//回転
        glm::mat4 matTranslation;	//平行移動

    };
}

#endif