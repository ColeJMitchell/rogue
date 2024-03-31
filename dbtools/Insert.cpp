//
// Created by cojmi on 3/14/2024.
//

#include <iostream>
#include "Insert.h"
#include <sqlite3.h>

void Insert::set_path(std::string path) {
    relative_path = path;
}


//adds player into the database with an id that is the same as the parameter
void Insert::add_Player(int id) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int health = 20;
    int gold = 0;
    int experience =0;
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "INSERT INTO players";
    sql += " ( id, health, gold, experience ) ";
    sql += "VALUES (";
    sql += std::to_string(id);
    sql += ", ";
    sql += std::to_string(health);
    sql += ", ";
    sql += std::to_string(gold);
    sql += ", ";
    sql += std::to_string(experience);
    sql += ");";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0,
                           0,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
}


//adds an item into the game_items table with row values equal to the function parameters
void Insert::add_Item(int id, std::string name, int damage, int amount,int row, int col) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "INSERT INTO game_items";
    sql += " ( id, name, damage, amount, row, col ) ";
    sql += "VALUES( ";
    sql += std::to_string(id);
    sql += ", \"";
    sql += name;
    sql += "\", ";
    sql += std::to_string(damage);
    sql +=", ";
    sql += std::to_string(amount);
    sql += ", ";
    sql += std::to_string(row);
    sql += ", ";
    sql += std::to_string(col);
    sql += " );";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0,
                           0,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
}


//adds an item into the inventory table with row values equal to the function parameters
void Insert::add_Inventory(int id, std::string name, int damage) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "INSERT INTO inventory";
    sql += " ( id, name, damage ) ";
    sql += "VALUES " ;
    sql +=  "( ";
    sql += std::to_string(id);
    sql += ", \"";
    sql += name;
    sql += "\", ";
    sql += std::to_string(damage);
    sql += ");";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0,
                           0,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
}

//adds an enemy into the game by adding a row to the game_enemies table with values equal to the function parameters
void Insert::add_enemy(int id, std::string name, int health, int damage, int row, int col){
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "INSERT INTO game_enemies";
    sql += " ( id, name, damage, health, row, col ) ";
    sql += "VALUES (";
    sql += std::to_string(id);
    sql += ", \"";
    sql += name;
    sql += "\", ";
    sql += std::to_string(health);
    sql += ", ";
    sql += std::to_string(damage);
    sql += " ,";
    sql += std::to_string(row);
    sql += ", ";
    sql += std::to_string(col);
    sql += ");";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0,
                           0,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);

}

