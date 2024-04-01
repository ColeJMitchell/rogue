//
// Created by cojmi on 3/14/2024.
//
#include <string>
#include <iostream>
#include "Game.h"
#include "Update.h"
#include "Select.h"
#include "Insert.h"
#include "Log.h"
Update u3;
Select s3;
Insert i3;
Game::Game(std::string databasePath){
    s3.set_path(databasePath);
    u3.set_path(databasePath);
    i3.set_path(databasePath);
}

//adds all the enemies to current game by using the dungeon lookup table starts at row count so multiple games can run at same time
std::vector<int> Game::add_all_enemies(Log &logger){
    std::vector<int> v;
    int c = s3.get_row_count("game_enemies");
    v.push_back(c);
    logger << "Emu spawned at row = 25 col = 25 id = "<<c<<"\n";
    spawn_enemy(c++,"Emu",25,25);
    v.push_back(c);
    logger << "Bat spawned at row = 15 col = 25 id = "<<c<<"\n";
    spawn_enemy(c++,"Bat",15,25);
    v.push_back(c);
    logger << "Zombie spawned at row = 30 col = 40 id = "<<c<<"\n";
    spawn_enemy(c++,"Zombie",30,40);
    v.push_back(c);
    logger << "Snake spawned at row = 27 col = 41 id = "<<c<<"\n";
    spawn_enemy(c++,"Snake",27,41);
    v.push_back(c);
    logger << "Hobgoblin spawned at row = 25 col = 42 id = "<<c<<"\n";
    spawn_enemy(c++,"Hobgoblin",25,42);
    v.push_back(c);
    logger << "Zombie spawned at row = 30 col = 60 id = "<<c<<"\n";
    spawn_enemy(c++,"Zombie",30,60);
    v.push_back(c);
    logger << "Snake spawned at row = 27 col = 60 id = "<<c<<"\n";
    spawn_enemy(c++,"Snake",27,60);
    v.push_back(c);
    logger << "Hobgoblin spawned at row = 25 col = 60 id = "<<c<<"\n";
    spawn_enemy(c++,"Hobgoblin",25,60);
    v.push_back(c);
    logger << "Dragon spawned at row = 13 col = 66 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",13,66);
    v.push_back(c);
    logger << "Dragon spawned at row = 39 col = 57 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",39,57);
    v.push_back(c);
    logger << "Dragon spawned at row = 20 col = 60 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",20,60);
    v.push_back(c);
    logger << "Dragon spawned at row = 22 col = 56 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",22,56);
    v.push_back(c);
    logger << "Dragon spawned at row = 39 col = 65 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",39,65);
    v.push_back(c);
    logger << "Dragon spawned at row = 30 col = 68 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",30,68);
    v.push_back(c);
    logger << "Dragon spawned at row = 37 col = 67 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",37,67);
    v.push_back(c);
    logger << "Dragon spawned at row = 39 col = 64 id = "<<c<<"\n";
    spawn_enemy(c++,"Dragon",39,64);
    return v;
}

//adds all the items to current game by using the dungeon lookup table starts at row count so multiple games can run at same time
std::vector<int> Game::add_all_items(Log &logger){
    std::vector<int> v;
    int c = s3.get_row_count("game_items");
    v.push_back(c);
    logger << "Amulet spawned at row = 39 col = 71 id = "<<c<<"\n";
    spawn_item(c++,"Amulet",39,71);
    v.push_back(c);
    logger << "Health_potion spawned at row = 30 col = 65 id = "<<c<<"\n";
    spawn_item(c++,"Health_potion",30,65);
    v.push_back(c);
    logger << "Health_potion spawned at row = 14 col = 70 id = "<<c<<"\n";
    spawn_item(c++,"Health_potion",14,70);
    v.push_back(c);
    logger << "Health_potion spawned at row = 12 col = 66 id = "<<c<<"\n";
    spawn_item(c++,"Health_potion",12,66);
    v.push_back(c);
    logger << "Health_potion spawned at row = 35 col = 62 id = "<<c<<"\n";
    spawn_item(c++,"Health_potion",35,62);
    return v;
}

//helper function for spawning enemies
void Game::spawn_enemy(int id, std::string name, int row, int col) {
    std::vector<std::string> v;
    v = s3.get_one_row_string("dungeon_enemies",name);
    i3.add_enemy(id,v[0],std::stoi(v[1]),std::stoi(v[2]),row,col);
}

//helper function for spawning items
void Game::spawn_item(int id, std::string name,int row, int col) {
    std::vector<std::string> v;
    v = s3.get_one_row_string("dungeon_items",name);
    i3.add_Item(id,v[0],std::stoi(v[1]),std::stoi(v[2]),row,col);
}