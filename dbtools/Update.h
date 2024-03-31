//
// Created by cojmi on 3/14/2024.
//

#ifndef REPO_LAB6_3_MITCHECJ_JIANGY_UPDATE_H
#define REPO_LAB6_3_MITCHECJ_JIANGY_UPDATE_H
#include <string>
//returns 1 if successful and 0 if failed for unit testing
class Update{
public:
    void damage_player_or_enemy(std::string table, int dmg, int id);
    void change_pos(int id, int amount, std::string column, std::string table);
    void add_health(int id, int health);
    void set_path(std::string path);
private:
    std::string relative_path;
};

#endif //REPO_LAB6_3_MITCHECJ_JIANGY_UPDATE_H
