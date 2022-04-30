#include "../header/Stage.hpp"


// ##################################### コンストラクタ ##################################### 
Stage::Stage()
{
    //brick_sprite = FrameWork::LoadTexture("asset/texture/brickChip.png");    

    //grid = std::make_shared<std::vector<byte>>();

    for(int i = 0; i < 100; i++)
    {
        //grid->push_back(0x01);
    }




}

// ##################################### 更新 ##################################### 
void Stage::Update()
{

}

// ##################################### 描画 ##################################### 
void Stage::Renderer()
{    

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            /*
            if(grid->at(i * 9 + j) == 0x01)
            {
                //FrameWork::RenderGraph(FrameWork::GetCurrentCamera()->getViewOrthographic(),glm::vec3(100,100,0),brick_sprite); 
            }
            */
        }
    }

}

// ##################################### デストラクタ ##################################### 
Stage::~Stage()
{

}