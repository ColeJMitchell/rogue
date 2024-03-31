//
// Created by cojmi on 3/14/2024.
//

#ifndef REPO_LAB6_3_MITCHECJ_JIANGY_DELETE_H
#define REPO_LAB6_3_MITCHECJ_JIANGY_DELETE_H
#include <string>
class Delete{
public:
void set_path(std::string path);
void delete_row(int id, std::string table);
private:
    std::string relative_path;


};
#endif //REPO_LAB6_3_MITCHECJ_JIANGY_DELETE_H
