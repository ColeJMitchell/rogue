//
// Created by Yunting Jiang on 3/25/2024.
//

#include "HallwayCoor.h"
HallwayCoor::HallwayCoor(int col, int row) : Coordinate(col, row), appear(false) {
    // Initialize base class using initializer list, and initialize appear to false
}

//return the value of appear
bool HallwayCoor::get_appear(){
    return appear;
}

//check if player is at this coordinate
bool HallwayCoor::if_at_this_Coor(int col1, int row1){
    if(get_col() == col1 && get_row() == row1){
        return true;
    }
    return false;
}

//set appear to be true
void HallwayCoor:: set_appear(){
    appear=true;
}