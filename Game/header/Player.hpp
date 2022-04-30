#ifndef ___PLAYER_HPP_
#define ___PLAYER_HPP_

#include "../../FrameWork/header/FrameWork.hpp"

class Player : public FrameWork::GameObject
{
public:
    Player();
    ~Player();

    void Update();
    void Render();

private:

    
    FrameWork::Texture texture;


    glm::vec3 position;
    float speed;





};

#endif
