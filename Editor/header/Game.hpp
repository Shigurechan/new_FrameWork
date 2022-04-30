#ifndef ___GAME_HPP_
#define ___GAME_HPP_


/*#########################################################################
# Camera 設定

説明
	
###########################################################################*/

#include "../FrameWork/header/FrameWork.hpp"

class Player;
class Stage;
class Game : public FrameWork::Scene
{
public:

    Game();
    ~Game();

    virtual void Update();
    virtual void Renderer();

private:

    std::shared_ptr<Player> player;
    std::shared_ptr<Stage> stage;



};

#endif
