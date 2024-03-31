//
// Created by cojmi on 3/18/2024.
//

#include "Select.h"
#include <iostream>
#include <sqlite3.h>

void Select::set_path(std::string path) {
    relative_path = path;
}

//callback for finding number of rows in a table;
int Select::cb_size(void *data, int argc, char **argv, char **azColName) {
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    } else {
// Store size in passed integer variable.
        int *obj = (int *) data;
        *obj = atoi(argv[0]);
    }
    return 0;
}

//ca;l back for selecting a row from a table as a vector of strings
int Select::cb_select_row(void *data, int argc, char **argv, char **azColName)
{
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    std::vector<std::string> *dv = (std::vector<std::string> *) data;
    for (int i = 0; i < argc; i++) {
        dv->push_back((argv[i] ? std::string(argv[i]) : "NULL"));
    }
    return 0;
}

//callback for pulling one integer value from the table
int Select::cb_select_one(void *data, int argc, char **argv, char **azColName) {
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    } else {
        int *obj = (int *) data;
        *obj = atoi(argv[0]);
    }
    return 0;
}

//gets one integer entry in a table based on a passed id
int Select::get_one_entry(std::string table, std::string column, int id) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "SELECT ";
    sql += column;
    sql += " FROM ";
    sql += table;
    sql += " WHERE id=";
    sql += std::to_string(id);
    sql += ";";
    int result =0;
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           cb_select_one,
                           (void *) &result,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
    return result;
}

//returns row based on passed id
std::vector<std::string> Select::get_one_row_id(std::string table, int id) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "SELECT ";
    sql += "*";
    sql += " FROM ";
    sql += table;
    sql += " WHERE id=";
    sql += std::to_string(id);
    sql += ";";
    std::vector<std::string> result;
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           cb_select_row,
                           (void *) &result,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
    return result;
}

//gets a row from a table based on a specified name of enemy or item, used for lookup on dungeon table
std::vector<std::string> Select::get_one_row_string(std::string table, std::string name) {
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "SELECT ";
    sql += "*";
    sql += " FROM ";
    sql += table;
    sql += " WHERE name= \"";
    sql += name;
    sql += "\" ;";
    std::vector<std::string> result;
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           cb_select_row,
                           (void *) &result,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
    return result;
}

//returns the number of rows in table passed as a parameter, used to calculated what ids should be when there are concurrent games
int Select::get_row_count(std::string table){
    sqlite3 *curr_db;
    int rc = sqlite3_open(relative_path.c_str(), &curr_db);
    int retCode = 0;
    char *zErrMsg = 0;
    std::string sql = "SELECT COUNT(*)";
    sql += " FROM ";
    sql += table;
    sql += " ;";
    int result=0;
    retCode = sqlite3_exec(curr_db,
                           sql.c_str(),
                           cb_size,
                           (void *) &result,
                           &zErrMsg);
    if (retCode != SQLITE_OK) {
        std::cerr << sql
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(curr_db);
    return result;

}

