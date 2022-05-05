#include "../header/Stage.hpp"
#include "../header/Brick.hpp"
#include "../header/Generate_Dungeon.hpp"

#include "../../FrameWork/header/FrameWork.hpp"
#include <memory>

// ##################################### コンストラクタ ##################################### 
Stage::Stage()
{
    stage.resize( (int)(FrameWork::GetCurrentWindow()->getSize().x / 24) * (int)(FrameWork::GetCurrentWindow()->getSize().y / 24) );
    std::fill(stage.begin(),stage.end(),(byte)0x00);

    sprite = FrameWork::LoadTexture("asset/texture/brickChip.png");


    dungeon = std::make_shared<Generate_Dungeon>(glm::ivec2((FrameWork::GetCurrentWindow()->getSize().x / 24),(FrameWork::GetCurrentWindow()->getSize().y / 24)),glm::ivec2(3,3));
    dungeon->setGenerate();
    //printf("aaaa\n");
    stage = dungeon->getStage();

    int xNum = (int)(FrameWork::GetCurrentWindow()->getSize().x / 24);
    int yNum = (int)(FrameWork::GetCurrentWindow()->getSize().y / 24);

    //std::cout<<"X: " << xNum<<std::endl;
    //std::cout<<"Y: " << yNum<<std::endl;
    //std::cout<<"Y * X: " << yNum * xNum<<std::endl;


    for(int i = 0; i< yNum; i++)
    {
        for(int j = 0; j < xNum; j++)
        {
            //std::cout<<(xNum * i + j)<<std::endl;
            switch(stage.at(xNum * i + j))
            {
                case 0x00:
                {
                    printf("*");
                }
                break;

                case 0x01:
                {
                    printf("A");
                }
                break;

                case 0x02:
                {
                    printf("B");
                }
                break;

                case 0x03:
                {
                    printf("C");
                }
                break;

                case 0x04:
                {
                    printf("D");
                }
                break;

                case 0x05:
                {
                    printf("E");
                }
                break;
                
                case 0x06:
                {
                    printf("F");
                }
                break;
                
                case 0x07:
                {
                    printf("G");
                }
                break;
                
                case 0x08:
                {
                    printf("H");
                }
                break;
                
                case 0x09:
                {
                    printf("I");
                }
                break;  


                case 0x0A:
                {
                    printf("J");
                }
                break;


                case 0x0B:
                {
                    printf("K");
                }
                break;


                case 0x0C:
                {
                    printf("L");
                }
                break;


                case 0x0D:
                {
                    printf("M");
                }
                break;


                case 0x0E:
                {
                    printf("N");
                }
                break;


                case 0x0F:
                {
                    printf("N");
                }
                break;

                case (byte)0xFF:
                {
                    printf("+");
                }
                break;



            }
            
        }
        
        printf("\n");
    }


}
// ##################################### 更新 ##################################### 
void Stage::Update()
{

}

// ##################################### 描画 ##################################### 
void Stage::Renderer()
{    
    //FrameWork::RenderGraph(FrameWork::currentCamera->getViewOrthographic(),glm::vec3(24,24,-2),sprite);

    for(int i = 0; i < (FrameWork::GetCurrentWindow()->getSize().y / 24); i++)
    {
        for(int j = 0; j < (FrameWork::GetCurrentWindow()->getSize().x / 24); j++)
        {
            switch(stage.at(i * (FrameWork::GetCurrentWindow()->getSize().x / 24) + j ))
            {
                case (byte)0xFF:
                {
                    //printf("っっｆ\n");
                    FrameWork::RenderGraph(FrameWork::currentCamera->getViewOrthographic(),glm::vec3(24 * j,24 * i,-3),sprite);
                }
                break;
            }
        }
}
    }

// ##################################### デストラクタ ##################################### 
Stage::~Stage()
{
    FrameWork::DeleteTexture(sprite);
}