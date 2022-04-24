#include "../header/GameObject.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::GameObject::GameObject()
{
    layer = 0;
}

// ##################################### tag　設定 ##################################### 
void FrameWork::GameObject::setTag(std::string str)
{
    tag = str;
}

// ##################################### tag　取得 ##################################### 
std::string FrameWork::GameObject::getTag()
{
    return tag;  
}

// ##################################### Layer 設定 ##################################### 
void FrameWork::GameObject::setLayer(int s)
{
    layer = s;
}

// ##################################### Layer 取得 ##################################### 
int FrameWork::GameObject::getLayer()
{
    return layer;
}

// ##################################### デストラクタ ##################################### 
FrameWork::GameObject::~GameObject()
{
    
}
