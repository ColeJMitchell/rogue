//
// Created by cojmi on 3/14/2024.
//
#include <iostream>
#include "Delete.h"
#include <sqlite3.h>
void Delete::set_path(std::string path) {
    relative_path = path;
}

//deletes a row in the database based on the id and table parameters
void Delete::delete_row(int id, std::string table){
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "DELETE FROM ";
    sql += table;
    sql += " WHERE id = ";
    sql += std::to_string(id);
    sql += ";";
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           0, // no call back needed for Delete
                           0, // no data structure needed
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
