//
// Created by Yunting Jiang on 3/24/2024.
//

#ifndef REPO_LAB6_5_MITCHECJ_JIANGY_ROOM_H
#define REPO_LAB6_5_MITCHECJ_JIANGY_ROOM_H
#include "Coordinate.h"
#include <vector>
class Room {
public:
    Room(std::vector<Coordinate> lists,int colMax, int rowMax, int offsetc, int offsetr);
    bool if_at_entrance_exit(int row, int col);
    void reload_room();
    void appear_or_not(int col, int row);
    bool get_appear();
    void first_room();
    int get_colMax();
    int get_rowMax();
    int get_offsetr();
    int get_offsetc();
    char buffer_value(int col, int row);
    bool if_at_this_room(int col, int row);
    bool if_entrance_around(int col, int row);

private:
    std::vector<Coordinate> entrance_or_exit;
    int row_max;//the height of room
    int col_max;//the length of room
    int offsetc;//the col offset
    int offsetr;//the row offset
    std::vector<std::vector<char>> buffer;
    bool appear=false;//if this dungeon appears in the map
};


#endif //REPO_LAB6_5_MITCHECJ_JIANGY_ROOM_H
