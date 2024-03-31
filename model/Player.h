//
// Created by cojmi on 3/14/2024.
//

#ifndef REPO_LAB6_3_MITCHECJ_JIANGY_PLAYER_H
#define REPO_LAB6_3_MITCHECJ_JIANGY_PLAYER_H
class Player{
public:
    void create_new_player(int id);
    void update_player_pos(int id, int row, int col);
    void remove_player(int id);
    void update_player_row(int id, int row);
    void update_player_col(int id, int col);
};
#endif //REPO_LAB6_3_MITCHECJ_JIANGY_PLAYER_H
