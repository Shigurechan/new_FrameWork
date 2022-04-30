#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_


/*#########################################################################
# Stage 

説明
	
###########################################################################*/

#include "../../FrameWork/header/FrameWork.hpp"
#include "Brick.hpp"

class Game;
class Stage
{
public:

    Stage();
    ~Stage();

    virtual void Update();
    virtual void Renderer();
private:

    std::shared_ptr<std::vector<byte>> grid;

    FrameWork::Texture brick_sprite;
   
};

#endif
