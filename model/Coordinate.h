//
// Created by Yunting Jiang on 3/23/2024.
//

#ifndef REPO_LAB6_5_MITCHECJ_JIANGY_COORDINATE_H
#define REPO_LAB6_5_MITCHECJ_JIANGY_COORDINATE_H


class Coordinate {
protected:
    int row;
    int col;
public:
    Coordinate(int col, int row);
    int get_row();
    int get_col();
};


#endif //REPO_LAB6_5_MITCHECJ_JIANGY_COORDINATE_H
