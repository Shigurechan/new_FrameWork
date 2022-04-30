#include "../header/Entry.hpp"
#include "../header/Brick.hpp"


// ##################################### コンストラクタ ##################################### 
Brick::Brick(glm::ivec2 pos) : FrameWork::GameObject()
{
    position = pos;
    texture = FrameWork::LoadTexture("asset/texture/brickChip.png");    
}

// ##################################### 更新 ##################################### 
void Brick::Update()
{
    
}

// ##################################### 描画 ##################################### 
void Brick::Render()
{
    FrameWork::RenderGraph(FrameWork::GetCurrentCamera()->getViewOrthographic(),glm::vec3(position,0),texture); 
}

// ##################################### デストラクタ ##################################### 
Brick::~Brick()
{
    
}
