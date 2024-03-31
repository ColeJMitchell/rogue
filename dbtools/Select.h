//
// Created by cojmi on 3/18/2024.
//

#ifndef REPO_LAB6_3_MITCHECJ_JIANGY_SELECT_H
#define REPO_LAB6_3_MITCHECJ_JIANGY_SELECT_H
#include <string>
#include <vector>

class Select{
public:
    static int cb_select_row(void *data, int argc, char **argv, char **azColName);
    static int cb_select_one(void *data, int argc, char **argv, char **azColName);
    static int cb_size(void *data, int argc, char **argv, char **azColName);
    static std::string cb_select_name(void *data, int argc, char **argv, char **azColName);

    int get_one_entry(std::string table, std::string column, int id);
    std::vector<std::string> get_one_row_id(std::string table, int id);
    std::vector<std::string> get_one_row_string(std::string table, std::string name);
    std::string get_one_name(std::string table, int id);
    int get_row_count(std::string table);

    void set_path(std::string path);
private:
    std::string relative_path;

};
#endif //REPO_LAB6_3_MITCHECJ_JIANGY_SELECT_H
