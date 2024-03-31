//
// Created by cojmi on 3/14/2024.
//

#include "Update.h"
#include <iostream>
#include <sqlite3.h>
void Update::set_path(std::string path) {
    relative_path = path;
}
void Update::add_health(int id, int health) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "UPDATE players";
    sql += " SET health = health + ";
    sql += std::to_string(health);
    sql += " WHERE id = ";
    sql += std::to_string(id);
    sql += ";";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0,
                           0,
                           &zErrMsg);
    if( retCode != SQLITE_OK ){
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
}

void Update::damage_player_or_enemy(std::string table, int dmg, int id) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "UPDATE ";
    sql += table;
    sql += " SET health = health - ";
    sql += std::to_string(dmg);
    sql += " WHERE id = ";
    sql += std::to_string(id);
    sql += ";";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0,
                           0,
                           &zErrMsg);
    if( retCode != SQLITE_OK ){
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
}


void Update::change_pos(int id, int amount, std::string column, std::string table) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "UPDATE ";
    sql += table;
    sql += " SET ";
    sql += column;
    sql += " = ";
    sql += std::to_string(amount);
    sql += " WHERE id = ";
    sql += std::to_string(id);
    sql += ";";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0,
                           0,
                           &zErrMsg);
    if( retCode != SQLITE_OK ){
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
}