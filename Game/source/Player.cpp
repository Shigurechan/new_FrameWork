#include "../header/Player.hpp"

// #####################################  コンストラクタ　##################################### 
Player::Player()
{
    texture = FrameWork::LoadTexture("asset/texture/player_up.png");
    speed = 100;

    position = glm::vec3(0,0,0);
}

// #####################################  更新　##################################### 
void Player::Update()
{
    if(FrameWork::GetKeyInput(GLFW_KEY_RIGHT) > 0)
    {    
        position.x += speed * FrameWork::GetCurrentWindow()->getDeltaTime();
    }
    else if(FrameWork::GetKeyInput(GLFW_KEY_LEFT) > 0)
    {
        position.x += -speed * FrameWork::GetCurrentWindow()->getDeltaTime();
    }

    if(FrameWork::GetKeyInput(GLFW_KEY_DOWN) > 0)
    {
        position.y += -speed * FrameWork::GetCurrentWindow()->getDeltaTime();
    }
    else if(FrameWork::GetKeyInput(GLFW_KEY_UP) > 0)
    {
        position.y += speed * FrameWork::GetCurrentWindow()->getDeltaTime();
    }
}

// #####################################  描画　##################################### 
void Player::Render()
{
    //FrameWork::RenderGraph_Size(FrameWork::GetCurrentCamera()->getViewOrthographic(),position,texture,glm::vec2(0,0),glm::vec2(39,39));
}

// #####################################  デストラクタ　##################################### 
Player::~Player()
{
    //FrameWork::DeleteTexture(texture);
}