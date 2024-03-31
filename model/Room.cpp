//
// Created by Yunting Jiang on 3/24/2024.
//

#include "Room.h"
//input some entrance or exit points for this room
Room::Room(std::vector<Coordinate> lists,int colMax, int rowMax, int offsetc, int offsetr){
    for(auto c : lists){
        entrance_or_exit.push_back(c);
    }
    row_max=rowMax;
    col_max=colMax;
    this->offsetc=offsetc;
    this->offsetr=offsetr;
   buffer.resize(row_max,std::vector<char>(col_max));

}

//check if the player is at the entrance or exit points
//this col and row should be whole_buffer coordinate
bool Room::if_at_entrance_exit(int col, int row){
    for(Coordinate x:entrance_or_exit){
        if(x.get_col() == col && x.get_row() == row){
            return true;
        }
    }
    return false;
}

void Room::reload_room(){
   if(appear) {
       for (int row = 0; row < row_max; row++) {
           for (int col = 0; col < col_max; col++) {
               if(if_at_entrance_exit(col+offsetc,row+offsetr))  buffer[row][col] = '+';//it is not necessary pro
               else if (row == 0)                buffer[row][col] = '-';
               else if (row == row_max - 1)      buffer[row][col] = '-';
               else if (col == 0)                buffer[row][col] = '|';
               else if (col == col_max - 1)      buffer[row][col] = '|';
               else                              buffer[row][col] = '.';
           }
       }
   }
   else{
       for (int row = 0; row < row_max; row++) {
           for (int col = 0; col < col_max; col++) {
               if (row == 0)                buffer[row][col] = ' ';
               else if (row == row_max - 1) buffer[row][col] = ' ';
               else if (col == 0)           buffer[row][col] = ' ';
               else if (col == col_max - 1) buffer[row][col] = ' ';
               else                         buffer[row][col] = ' ';
           }
       }
   }
}


//when appear=false and the player is at the entrance or exit point, appear=true
void Room::appear_or_not(int col, int row){
    if(if_at_entrance_exit(col,row)) {
        if (!appear) {
            appear = true;
        }
    }
}
void Room::first_room(){
    appear=true;
}

int Room::get_colMax(){
    return col_max;
}
int Room::get_rowMax(){
    return row_max;
}
int Room::get_offsetr(){
    return offsetr;
}
int Room::get_offsetc(){
    return offsetc;
}
char Room::buffer_value(int row, int col){
    return buffer[row][col];
}

bool Room::get_appear(){
    return appear;
}

bool Room::if_at_this_room(int col, int row){
    if(col>offsetc && col<col_max+offsetc-1
       && row>offsetr && row< row_max+offsetr-1){
        return true;
    }
    else{
        return false;
    }
}
//this is a helper function for setting constrain
//if the player has the same row or col with the extrance or exit point of this room, return true
bool Room::if_same_line(int col, int row){
    for(Coordinate c:entrance_or_exit){
        if(c.get_row()==row || c.get_col()==col){
            return true;
        }
    }
    return false;
}
