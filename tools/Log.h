//
// Created by cojmi on 3/13/2024.
//
#ifndef REPO_LAB3_MITCHECJ_JIANGY_LOG_H
#define REPO_LAB3_MITCHECJ_JIANGY_LOG_H
#include <fstream>
#include <string>

//adds strings, ints, or doubles to a text file, and has multiple methods for manipulating the file
class Log{
public:
    enum state{
        open,closed,flushed
    };
    Log();
    Log(Log &obj);
    void operator=(Log &obj);
    int some_data;
    state s;
    Log(const std::string& fileLocation);
    ~Log();
    Log& operator<<(std::string str);
    Log& operator<<(int integer);
    Log& operator<<(double d);
    void flush();
    void open_file(const std::string& file);
    void close();
    std::string return_state();
    void append(char file[]);
private:
    std::ofstream fh;
};

#endif //REPO_LAB3_MITCHECJ_JIANGY_LOG_H