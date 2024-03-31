//
// Created by cojmi on 3/13/2024.
//
#include <iostream>
#include "Select.h"
#include "Update.h"
#include "Delete.h"
#include "Insert.h"
#include "Dungeon.h"
#include "Game.h"
#include <iostream>
Insert i1;
Delete d1;
Select s1;
Dungeon d;
Game g1;
int main(int argc, char **argv) {
    s1.set_path("../database/rogue.sqlite");
    i1.set_path("../database/rogue.sqlite");
    //i1.add_enemy(500,"Test_enemy",100,100);
    //i1.add_enemy(2,"s",1,1);
    std::cout << s1.get_row_count("game_enemies");
    //i1.add_Inventory(1,"mace",1);
    //s1.get_one_row("players",2);
    //std::cout<< g1.id_counter;
}