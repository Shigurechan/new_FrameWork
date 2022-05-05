#include "../header/Generate_Dungeon.hpp"
#include "../../FrameWork/header/FrameWork.hpp"
#include <glm/glm.hpp>
#include <algorithm>


// ##################################### コンストラクタ ##################################### 
Generate_Dungeon::Generate_Dungeon(glm::ivec2 s,glm::ivec2 div = glm::ivec2(0,0))
{
    minDivsion_X = 3;
    minDivsion_Y = 3;

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
    int num = -1;
    for(std::vector<Area>::iterator itr = area.begin(); itr != area.end(); itr++)
    {
        if(map.size < itr->size)
        {

            map = *itr;
            num = i;

//            std::cout<<map.size<<std::endl;
        }
        i++;
    }
    
    if(num != -1)
    {
        area.erase(area.begin() + num);
    }
    else
    {
        std::cout<< "Error: 削除するエリアがありません。"<<std::endl;
    }
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


            std::cout<<"    map.start.y: " << map.start.y<<std::endl;
//            std::cout<<map.size<<std::endl;

        }

//            std::cout<<"    map.start.y: " << map.start.y<<std::endl;

    }

            std::cout<<"return  map.start.y: " << map.start.y<<std::endl;
//            std::cout<<std::endl;
//            std::cout<<std::endl;
//            std::cout<<std::endl;



    
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
int Generate_Dungeon::GetCheckLineDown_Y(glm::ivec2 start,int posX)
{
    byte b = stage.at( (allSize.x * start.y) + start.x + posX);
    int y = 0;
    for(int i = start.y; i < allSize.y; i++)
    {
        if(stage.at( (allSize.x * i + start.x) + posX) != b)
        {
            return y;
        }

        y++;
    }

    return y;
}

// ##################################### X軸からYの長さを取得 ##################################### 
int Generate_Dungeon::GetCheckLineUp_Y(glm::ivec2 start,int posX)
{
    byte b = stage.at( (allSize.x * start.y) + start.x + posX);
    int y = 0;
    for(int i = start.y; i > 0; i--)
    {
        if(stage.at( (allSize.x * i + start.x) + posX) != b)
        {
            return y;
        }

        y++;
    }

    return y;
}

// ##################################### Y軸からXの長さを取得 ##################################### 
int Generate_Dungeon::GetCheckLineRight(glm::ivec2 start,int posY)
{
    byte b = stage.at( (allSize.x * (start.y + posY) ) + start.x);
    int x = 0;
    for(int i = start.x; i < allSize.x; i++)
    {        
        if(stage.at( (allSize.x * posY) + i) != b)
        {
            return x;
        } 
               
        x++;
    }

    return x;    
}

// ##################################### Y軸からXの長さを取得 ##################################### 
int Generate_Dungeon::GetCheckLineLeft(glm::ivec2 start,int posY)
{
    byte b = stage.at( (allSize.x * (start.y + posY) ) + start.x);
    int x = 0;
    for(int i = start.x; i > 0; i--)
    {        
        if(stage.at( (allSize.x * posY) + i) != b)
        {
            return x;
        } 
               
        x++;
    }

    return x;    
}



// ##################################### ステージに値を設定 ##################################### 
void Generate_Dungeon::SetStage(glm::ivec2 pos,byte b)
{
    stage.at((allSize.x * pos.y) + pos.x) = b;
}

// ##################################### ステージに値を取得 ##################################### 
byte Generate_Dungeon::GetStage(glm::ivec2 pos)
{
    return stage.at((allSize.x * pos.y) + pos.x);
}

// ##################################### X軸に分割ラインを引く ##################################### 
void Generate_Dungeon::SetLine_X(int posY)
{
    for(int x = 0; x < allSize.x; x++)
    {
        SetStage(glm::ivec2(x,posY),flag);
    }
}

// ##################################### Y軸に分割ラインを引く ##################################### 
void Generate_Dungeon::SetLine_Y(int posX)
{
    for(int x = 0; x < allSize.y; x++)
    {
        SetStage(glm::ivec2(posX,x),flag);
    }
}

// ##################################### Xライン分割 ##################################### 
void Generate_Dungeon::SetDivLine_X()
{
    const int num = allSize.y / (divsion_X + 1);
    
    int n = num / 2;


    std::cout<<minDivsion_X<<std::endl;
    std::cout<<num - minDivsion_X<<std::endl;



    int pos = FrameWork::GetRandom(minDivsion_X, num);

    
    SetLine_X(pos);


    int number = num;

    flag++;
   // number += num;
    pos = FrameWork::GetRandom(minDivsion_X, num);
    SetLine_X(number + pos);


    flag++;
    number += num;
    pos = FrameWork::GetRandom(minDivsion_X, num);
    SetLine_X(number + pos);




}

// ##################################### Yライン分割 ##################################### 
void Generate_Dungeon::SetDivLine_Y()
{
    int num = allSize.x / (divsion_Y + 1);

}

// #####################################  エリアを作成 ##################################### 
void Generate_Dungeon::SetCreateArea()
{
    int num = divsion_X * divsion_Y;

    glm::ivec2 start = glm::ivec2(0,0);
    for(int i = 0; i< num; i++)
    {
        glm::ivec2 size = GetArea(start);
        //SetArea(start,size,(byte)0xFF);
    }
}

// #####################################  エリアを取得 ##################################### 
glm::ivec2 Generate_Dungeon::GetArea(glm::ivec2 start)
{
    glm::ivec2 size = glm::ivec2(0,0);
    byte b = GetStage(start);
    for(int x = 0; x < allSize.x; x++)
    {
        if(GetStage(start + glm::ivec2(x,0)) != b)
        {
            break;
        }
        else
        {
            size.x += 1;
        }
    }


    for(int y = 0; y < allSize.y; y++)
    {
        if(GetStage(start + glm::ivec2(0,y)) != b)
        {
            break;
        }
        else
        {
            size.y += 1;
        }
    }
    



    return size;
}

// ##################################### ステージを生成 ##################################### 
void Generate_Dungeon::setGenerate()
{
    SetDivLine_X();     //横分割
    //SetDivLine_Y();     //縦分割

    //SetCreateArea();    //エリアを作成



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