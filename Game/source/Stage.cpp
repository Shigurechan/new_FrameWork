#include "../header/Stage.hpp"
#include "../header/Brick.hpp"

// ##################################### コンストラクタ ##################################### 
Stage::Stage()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 00; j++)
        {
            grid[i][j] = 0x01;
        }    
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(grid[i][j] = 0x01)
            {
                object.push_back(std::make_shared<Brick>(glm::ivec2(i * 24,j * 24)));
            }
            else
            {
                object.push_back(nullptr);
            }
        
        }    
    }
}

// ##################################### 更新 ##################################### 
void Stage::Update()
{

}

// ##################################### 描画 ##################################### 
void Stage::Renderer()
{    
    for(std::vector<std::shared_ptr<FrameWork::GameObject>>::iterator itr = object.begin(); itr != object.end(); itr++)
    {
        (*itr)->Render();
    }


}

// ##################################### デストラクタ ##################################### 
Stage::~Stage()
{

}