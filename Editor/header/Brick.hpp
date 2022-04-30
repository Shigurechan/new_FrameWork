#ifndef ___BRICK_HPP_
#define ___BRICK_HPP_


/*#########################################################################
# Brick

説明
	
###########################################################################*/

#include "../../FrameWork/header/FrameWork.hpp"

class Brick : public FrameWork::GameObject
{
public:

    Brick();
    ~Brick();

    virtual void Update();
    virtual void Renderer();

    static glm::ivec2 size;
private:

    FrameWork::Texture texture;
    
    



};

#endif
