#include "../header/Game.hpp"
#include "../header/Player.hpp"
#include "../header/Stage.hpp"

// ##################################### コンストラクタ ##################################### 
Game::Game(): Scene()
{
    player = std::make_shared<Player>();
    stage = std::make_shared<Stage>();
}

// ##################################### 更新 ##################################### 
void Game::Update()
{
    player->Update();    
    stage->Update();
}

// ##################################### 描画 ##################################### 
void Game::Renderer()
{
    player->Render();     
    stage->Renderer();
}

// ##################################### デストラクタ ##################################### 
Game::~Game()
{
    
}
