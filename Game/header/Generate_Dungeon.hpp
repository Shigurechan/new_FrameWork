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
        glm::ivec2 start;   //座標
        glm::ivec2 end;     //座標
    };

    void DeleteMaxArea();
    Area GetMaxArea();
    void SetArea(glm::ivec2 start,glm::ivec2 size,byte b);
    glm::ivec2 GetArea(glm::ivec2 start);

    void SetDivLine_X();
    void SetDivLine_Y();

    void SetStage(glm::ivec2 pos,byte b);
    byte GetStage(glm::ivec2 pos); 
    
    int GetCheckLineDown_Y(glm::ivec2 start,int posX);
    int GetCheckLineUp_Y(glm::ivec2 start,int posX);

    int GetCheckLineRight(glm::ivec2 start,int posY);
    int GetCheckLineLeft(glm::ivec2 start,int posY);

    void SetLine_X(int posY);
    void SetLine_Y(int posX);  


    void SetCreateArea();
    void Generate();



    std::vector<byte> stage;    //グリッド
    byte flag = 0x01;           //番号           
    int divsion_X;              //分割量　X
    int divsion_Y;              //分割量　Y
    glm::ivec2 allSize;         //全体のサイズ
    std::vector<Area> area;     //エリア数
    std::vector<int> divLine_X; //X軸ライン分割の分割間隔
    std::vector<int> divLine_Y; //Y軸ライン分割の分割間隔
    int minDivsion_X;           //最低間隔数 X
    int minDivsion_Y;           //最低間隔数 Y


};

#endif
