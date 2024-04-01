//
// Created by cojmi on 3/14/2024.
//
#include "Player.h"
#include "Insert.h"
#include "Update.h"
#include "Delete.h"
Insert i;
Update u;
Delete d;
Player::Player(const std::string& databasePath){
    i.set_path(databasePath);
    u.set_path(databasePath);
}
void Player::create_new_player(int id) {

    i.add_Player(id);
}
void Player::update_player_pos(int id, int row, int col) {
    u.change_pos(id,row,"row","players");
    u.change_pos(id,row,"col","players");
}


