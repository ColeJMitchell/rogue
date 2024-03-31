//
// Created by cojmi on 3/14/2024.
//
#ifndef REPO_LAB6_3_MITCHECJ_JIANGY_INSERT_H
#define REPO_LAB6_3_MITCHECJ_JIANGY_INSERT_H
#include <string>
class Insert{
public:
void add_Player(int id);
void add_Inventory(int id, std::string name, int damage, int row, int col);
void add_Inventory(int id, std::string name, int damage);
void add_enemy(int id, std::string name, int health, int damage, int row, int col);
void add_Item(int id, std::string name, int damage, int amount, int row, int col);
void set_path(std::string path);
private:
    std::string relative_path;
};
#endif //REPO_LAB6_3_MITCHECJ_JIANGY_INSERT_H
