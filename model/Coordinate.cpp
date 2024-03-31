//
// Created by Yunting Jiang on 3/23/2024.
//

#include "Coordinate.h"
Coordinate::Coordinate(int col, int row){
    this->row=row;
    this->col=col;
}
int Coordinate::get_col() {
    return col;
}
int Coordinate::get_row() {
    return row;
}