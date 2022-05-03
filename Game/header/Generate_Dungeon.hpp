#ifndef ___GENERATE_DUNGEON_HPP_
#define ___GENERATE_DUNGEON_HPP_

#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <cstdarg>
#include <sys/types.h>
#include <glm/glm.hpp>

#include "../../FrameWork/header/FrameWork.hpp"

class Generate_Dungeon
{
private:

public:

    Generate_Dungeon(glm::ivec2 s,glm::ivec2 div);
    ~Generate_Dungeon();

    std::vector<byte> getStage();                       //ステージを取得
    void setGenerate();                                 //ステージ　生成
    void setReSetStage(glm::ivec2 s,glm::ivec2 div); //ステージの大きさを再設定
    void setDivisionNum_X(int x);                       //分割量　X
    void setDivisionNum_Y(int y);                       //分割量　Y

private:

    //エリア
    struct Area
    {
        int size;
        glm::ivec2 start;
        glm::ivec2 end;
    };

    void SetStage(glm::ivec2 start,glm::ivec2 pos,byte b);
    byte GetStage(glm::ivec2 start,glm::ivec2 pos); 
    void DeleteMaxArea();
    Area GetMaxArea();
    void SetArea(glm::ivec2 start,glm::ivec2 size,byte b);
    int GetCheckLine_Y(glm::ivec2 start,int posX);
    int GetCheckLine_X(glm::ivec2 start,int posY);
    void SetLine_X(int posY);
    void SetLine_Y(int posX);
    void Generate();
    
    std::vector<byte> stage;    //グリッド
    byte flag = 0x01;           //番号           
    int divsion_X;              //分割量　X
    int divsion_Y;              //分割量　Y
    glm::ivec2 allSize;         //全体のサイズ
    std::vector<Area> area;     //エリア数
    

};

#endif
