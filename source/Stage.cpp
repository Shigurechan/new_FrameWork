#include "../header/Stage.hpp"

// ##################################### コンストラクタ ##################################### 
Stage::Stage()
{
    brickChip = FrameWork::LoadTexture("asset/texture/brickChip.png");
}

// ##################################### 更新 ##################################### 
void Stage::Update()
{

}

// ##################################### 描画 ##################################### 
void Stage::Renderer()
{
    FrameWork::RenderGraph(FrameWork::GetCurrentCamera()->getViewOrthographic(),glm::vec3(100,100,0),brickChip);
}

// ##################################### デストラクタ ##################################### 
Stage::~Stage()
{

}