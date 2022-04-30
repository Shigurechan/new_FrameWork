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

    Brick(glm::ivec2 pos);
    ~Brick();

    virtual void Update();
    virtual void Render();

    
private:

    FrameWork::Texture texture;
    glm::ivec2 position;
    



};

#endif
