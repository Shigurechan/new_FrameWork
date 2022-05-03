#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_


/*#########################################################################
# Stage 

説明
	
###########################################################################*/

#include "../../FrameWork/header/FrameWork.hpp"
#include "Brick.hpp"

class Game;
class Generate_Dungeon;
class Stage
{
public:

    Stage();
    ~Stage();

    virtual void Update();
    virtual void Renderer();

    
private:

    std::vector<byte> stage;

    std::shared_ptr<Generate_Dungeon> dungeon;

    FrameWork::Texture sprite;


};

#endif
