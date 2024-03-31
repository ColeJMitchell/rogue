//
// Created by cojmi on 3/14/2024.
//

#ifndef REPO_LAB6_3_MITCHECJ_JIANGY_MODEL_H
#define REPO_LAB6_3_MITCHECJ_JIANGY_MODEL_H
#define ROWMAX 80
#define COLMAX 100
#include <vector>
#include "Room.h"
#include "Hallway.h"
class Model{
public:
    Model();
    int screen_page;
    int enemies_slain;
    void reload_dungeon();
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    char buffer_value(int row, int col);
    int max_rows(void);
    int max_cols(void);
    void remove_players();
    bool is_vertical(int col, int row);
    std::pair<bool, Direction> if_at_turning_point(int col, int row);
    int is_in_the_room(int col, int row);
    void set_constraint();
    void move_random(int id);
    void wipe_screen();
    int return_health();
private:
    std::vector<std::vector<char>> whole_buffer;
    std::vector<Room> rooms;
    std::vector<Hallway> hallways;
    int rowpos;
    int colpos;
    //these are constrains for moving
    int left;
    int right;
    int up;
    int down;
};
#endif //REPO_LAB6_3_MITCHECJ_JIANGY_MODEL_H
