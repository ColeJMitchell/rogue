//
// Created by Yunting Jiang on 3/25/2024.
//
//the buffer for the hallway is set to be at the origin with its height and length
//HallwayCoordinates are presented with the coordinates shown in the whole buffer
#include "Hallway.h"
#include <utility>
#include <iostream>
Hallway::Hallway(const std::vector<HallwayCoor>& input, int colMax, int rowMax, int offsetc, int offsetr) {
    for(HallwayCoor c: input){
        lists.push_back(c);
    }
    buffer.resize(rowMax,std::vector<char>(colMax));
    //not sure if these two are needed
    col_max=colMax;
    row_max=rowMax;
    this->offsetc=offsetc;
    this->offsetr=offsetr;
}

//check if any HallwayCoor will change to appear
void Hallway::appear_or_not(int col, int row){
    for(int i=0;i<lists.size()-1;i++){//size-1 making boundary, think about how to implement the entrance point
        if(lists[i].if_at_this_Coor(col, row)){
            if(!lists[i+1].get_appear()) {
                lists[i + 1].set_appear();
            }
            break;
        }
    }
}

//reload the buffer of this hallway, if the "appear" of one HallwayCoor is set to appear, this Coor will be shown as '+'
void Hallway::reload_hallway(){
    for(int i=0;i<lists.size();i++){
        int adjusted_row = lists[i].get_row() - offsetr;
        int adjusted_col = lists[i].get_col() - offsetc;

        if(adjusted_row >= 0 && adjusted_row < row_max &&
           adjusted_col >= 0 && adjusted_col < col_max) {
            if(lists[i].get_appear()) {
                if (i==0 || i==lists.size()-1) {buffer[adjusted_row][adjusted_col] = '+';}
                else {
                buffer[adjusted_row][adjusted_col] = '#';
                }
            } else {
                buffer[adjusted_row][adjusted_col] = ' ';
            }
        }
        else{
            std::cout<<lists[i].get_col()<<lists[i].get_row()<<"Hallway buffer out of boundary"<<std::endl;
        }
    }

}



char Hallway::buffer_value(int row, int col){
    return buffer[row][col];
}
int Hallway::get_rowMax() {
    return row_max;
}
int Hallway::get_colMax() {
    return col_max;
}
int Hallway::get_offsetr(){
    return offsetr;
}
int Hallway::get_offsetc(){
    return offsetc;
}
std::vector<HallwayCoor>& Hallway::get_lists(){
    return lists;
}