#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_


/*#########################################################################
# Stage 

説明
	
###########################################################################*/

#include "../FrameWork/header/FrameWork.hpp"

class Game;
class Stage
{
public:

    Stage();
    ~Stage();

    virtual void Update();
    virtual void Renderer();

private:

    FrameWork::Texture brickChip;
    



};

#endif
