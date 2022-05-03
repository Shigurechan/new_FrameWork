#include "../header/Generate_Dungeon.hpp"
#include "../../FrameWork/header/FrameWork.hpp"
#include <glm/glm.hpp>

// ##################################### コンストラクタ ##################################### 
Generate_Dungeon::Generate_Dungeon(glm::ivec2 s,glm::ivec2 div = glm::ivec2(0,0))
{
    setDivisionNum_X(div.x);
    setDivisionNum_Y(div.y);

    //printf("%d\n",s.y);

    allSize = s;
    stage.resize(s.x * s.y);
    area.resize(0);
    area.push_back(Area { s.x * s.y,glm::ivec2(0,0),s });
}


// ##################################### ステージ再設定 ##################################### 
void Generate_Dungeon::setReSetStage(glm::ivec2 s,glm::ivec2 div)
{
    setDivisionNum_X(div.x);
    setDivisionNum_Y(div.y);

    allSize = s;
    stage.resize(s.x * s.y);

    area.resize(0);
    area.push_back(Area { s.x * s.y,glm::ivec2(0,0),s });
}

// ##################################### 一番大きいエリアを削除 ##################################### 
void Generate_Dungeon::DeleteMaxArea()
{
    Area map = Area{0,glm::ivec2(0,0),glm::ivec2(allSize.x,allSize.y)};    
    int i = 0;
    int num = 0;
    for(std::vector<Area>::iterator itr = area.begin(); itr != area.end(); itr++)
    {
        if(map.size < itr->size)
        {
            map = *itr;
            num = i;
        }
        i++;
    }
    
    area.erase(area.begin() + num);
}

// ##################################### 一番大きいエリアを取得 ##################################### 
Generate_Dungeon::Area Generate_Dungeon::GetMaxArea()
{
    Area map = Area{0,glm::ivec2(0,0),glm::ivec2(0,0)};    
    for(std::vector<Area>::iterator itr = area.begin(); itr != area.end(); itr++)
    {
        if(map.size < itr->size)
        {
            map = *itr;


//            std::cout<<"    map.start.y: " << itr->size<<std::endl;

        }

            std::cout<<"    map.start.y: " << map.start.y<<std::endl;

    }

            std::cout<<"return  map.start.y: " << map.start.y<<std::endl;

    
    return map;
}

// ##################################### エリアに値を設定 ##################################### 
void Generate_Dungeon::SetArea(glm::ivec2 start,glm::ivec2 size,byte b)
{
    for(int y = start.y; y < start.y + size.y; y++)
    {
        for(int x = start.x; x < start.x + size.x; x++)
        {
            stage.at((y * allSize.x) + x) = b;
        }
    }

}

// ##################################### X軸からYの長さを取得 ##################################### 
/*
    説明
        マス目の数を返す
*/
int Generate_Dungeon::GetCheckLine_Y(glm::ivec2 start,int posX)
{
    byte b = stage.at( (allSize.x * start.y) + start.x + posX);
    int y = 0;
    for(int i = start.y; i < allSize.y; i++)
    {
        if(stage.at( (allSize.x * i + start.x) + posX) != b)
        {
            return y - 1;
        }

        y++;
    }

    return y;
}
   
// ##################################### Y軸からXの長さを取得 ##################################### 
int Generate_Dungeon::GetCheckLine_X(glm::ivec2 start,int posY)
{
    //std::cout<<"aaaaaaa "<< (allSize.x * (start.y + posY) ) + start.x -1 <<std::endl;
    byte b = stage.at( (allSize.x * (start.y + posY) ) + start.x);
    int x = 0;
    for(int i = start.x; i < allSize.x; i++)
    {        
        
//        std::cout<<(allSize.x * posY) + i<<std::endl;
        if(stage.at( (allSize.x * posY) + i) != b)
        {
            return x;
        } 
               
        x++;
    }

    return x;    
}

// ##################################### ステージに値を設定 ##################################### 
void Generate_Dungeon::SetStage(glm::ivec2 start,glm::ivec2 pos,byte b)
{
    stage.at((allSize.x * (pos.y + start.y)) + pos.x + start.x) = b;
}

// ##################################### ステージに値を取得 ##################################### 
byte Generate_Dungeon::GetStage(glm::ivec2 start,glm::ivec2 pos)
{
    return stage.at((allSize.x * (pos.y + start.y)) + pos.x + start.x);
}
// ##################################### X軸に分割ラインを引く ##################################### 
void Generate_Dungeon::SetLine_X(int posY)
{

//    printf("allSize.y: %d\n",posY);
    Area map = GetMaxArea();    //一番大きいエリアを取得

    int rangeX = GetCheckLine_X(map.start,posY);             //X軸のマス目の個数を取得
    SetArea(map.start,glm::ivec2(rangeX,posY),flag);         //範囲に値を設定

    glm::ivec2 s = map.end - (map.start + glm::ivec2(0,posY));

    DeleteMaxArea();   //一番大きいエリアを削除


    area.push_back(Area{ rangeX * posY,map.start,glm::ivec2(map.start.x + rangeX,map.start.y + posY) }); //エリアを追加


    flag++;

//    std::cout<<"posY: " << posY<<std::endl;

    int y = GetCheckLine_Y(map.start + glm::ivec2(0,posY),0);
//    std::cout<<"y:   " << y<<std::endl;



//    std::cout<< (map.start + glm::ivec2(rangeX,posY)).x<<std::endl;
//    std::cout<< (map.start + glm::ivec2(rangeX,posY)).y<<std::endl;
    SetArea(map.start + glm::ivec2(0,posY),glm::ivec2(rangeX,y),flag);         //範囲に値を設定
    area.push_back(Area{ s.x * s.y,map.start + glm::ivec2(0,posY),glm::ivec2(map.start.x + rangeX + s.x ,map.start.y + posY + s.y) }); //エリアを追加







}

// ##################################### Y軸に分割ラインを引く ##################################### 
void Generate_Dungeon::SetLine_Y(int pos)
{

}



// ##################################### ステージを生成 ##################################### 
void Generate_Dungeon::setGenerate()
{
    //std::cout<<divsion_X<<std::endl;
    for(int i = 0; i< 4; i++)
    {
        Area map = GetMaxArea();
        std::cout<<"map.end.y: " <<map.end.y<<std::endl;
        //std::cout<<"map.end.X: " <<map.end.x<<std::endl;

        //printf("random : %d\n",map.end.y - map.start.y);
        if( (map.end.y - map.start.y - 1) <= 6)
        {
            break;
        }

        SetLine_X(FrameWork::GetRandom(3,map.end.y - map.start.y - 1));
        //SetLine_X(29 - 1);
        //printf("aaaaa\n");
        flag++;
    }

    for(int i = 0; i< divsion_Y; i++)
    {
        //SetLine_Y(FrameWork::GetRandom(10,allSize.X));
    }
    
}

// #####################################  分割量 X ##################################### 
void Generate_Dungeon::setDivisionNum_X(int x)
{
    divsion_X = x;
}

// #####################################  分割量 Y ##################################### 
void Generate_Dungeon::setDivisionNum_Y(int y)
{
    divsion_Y = y;
}

// ##################################### ステージを取得 ##################################### 
std::vector<byte> Generate_Dungeon::getStage()
{
    return stage;
}

// ##################################### デストラクタ ##################################### 
Generate_Dungeon::~Generate_Dungeon()
{

}