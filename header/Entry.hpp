#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_


/*#########################################################################
# Camera 設定

説明
	
###########################################################################*/

#include "../FrameWork/header/FrameWork.hpp"

class Game;
class Entry : public FrameWork::Scene
{
public:

    Entry();
    ~Entry();

    virtual void Update();
    virtual void Renderer();

private:

    std::shared_ptr<Game> game;




};

#endif
