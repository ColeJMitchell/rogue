//
// Created by Yunting Jiang on 3/25/2024.
//

#ifndef REPO_LAB6_5_MITCHECJ_JIANGY_HALLWAYCOOR_H
#define REPO_LAB6_5_MITCHECJ_JIANGY_HALLWAYCOOR_H
#include "Coordinate.h"

class HallwayCoor : public Coordinate{
private:
    bool appear;
public:
   HallwayCoor(int col, int row);
    bool get_appear();
    bool if_at_this_Coor(int col, int row);
    void set_appear();
};


#endif //REPO_LAB6_5_MITCHECJ_JIANGY_HALLWAYCOOR_H
