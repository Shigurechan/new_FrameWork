#ifndef ___GAMEOBJECT_HPP_
#define ___GAMEOBJECT_HPP_

#include <iostream>

#include "Transform.hpp"

/*#########################################################################
# GameObjectクラス

説明

###########################################################################*/


namespace FrameWork
{
    class GameObject
    {
    public:
        GameObject();
        ~GameObject();

        virtual void Update() = 0;  //アップデート
        

        void setTag(std::string str);
        std::string getTag();    

        void setLayer(int s);
        int getLayer();

    private:
        std::string tag;    //タグ
        int layer;          //レイヤー

    };

}
#endif