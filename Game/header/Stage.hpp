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

    byte grid[10][10];
    std::vector<std::shared_ptr<FrameWork::GameObject>> object;


};

#endif
