//
// Created by Yunting Jiang on 3/25/2024.
//

#ifndef REPO_LAB6_5_MITCHECJ_JIANGY_HALLWAY_H
#define REPO_LAB6_5_MITCHECJ_JIANGY_HALLWAY_H
#include "HallwayCoor.h"
#include <vector>
enum class Direction{
    UpAndRight,
    UpAndLeft,
    DownAndRight,
    DownAndLeft,
    NotTurningPoint
};
class Hallway {
private:
    std::vector<HallwayCoor> lists;// the lists of Coordinates in this hallway
    std::vector<std::vector<char>> buffer;//the buffer shows the hallway
    int col_max;
    int row_max;
    int offsetc;
    int offsetr;
public:
    Hallway(const std::vector<HallwayCoor>& input,int colMax, int rowMax, int offsetc, int offsetr);
    void appear_or_not(int col, int row);
    void reload_hallway();
    void firstCoord();
    char buffer_value(int row, int col);
    int get_rowMax();
    int get_colMax();
    int get_offsetr();
    int get_offsetc();
    std::vector<HallwayCoor>& get_lists();
};


#endif //REPO_LAB6_5_MITCHECJ_JIANGY_HALLWAY_H
