//
// Created by cojmi on 3/13/2024.
//
#include "Log.h"
#include <iostream>
std::string name;
std::string file_location = "repo_lab3_mitchecj_jiangy.git";
Log::Log(){
    some_data = 0;
}
Log::Log(Log &obj)
{
    some_data = obj.some_data;
}
void Log::operator=(Log &obj)
{
    some_data = obj.some_data;
}

Log::Log(const std::string& fileLocation) {
    name = fileLocation;
    fh.open(fileLocation, std::ofstream::out | std::ofstream::app );
    s= open;
}

Log::~Log() {
    fh.close();
    s = closed;
}


//all of the methods that manipulate the file
//flushes the filehandler
void Log::flush(){
    fh.flush();
    s= flushed;
}
//opens empty file
void Log::open_file(const std::string& file){
    try {
        name = file;
        fh.open(file, std::ofstream::out);
        s = open;
    }
    catch(std::exception& e){
        std::cerr<<"Error opening"<<std::endl;
    }
}
//open file for appending
void Log::append(char file[]) {
    try {
        name=file;
        fh.open(file, std::ofstream::out  | std::ofstream::app );
        s = open;
    }
    catch(std::exception& e){
        std::cerr<<"Error opening"<<std::endl;
    }
}
//closes the file
void Log::close(){
    try{
        fh.close();
        s = closed;
    }
    catch(const std::exception& e){
        std::cerr<< "Exception during file closing"<<e.what()<<std::endl;
    }
}

//all of the overloads
//overloading string
Log& Log::operator<<(std::string str) {
    fh << str;
    fh.flush();
    s= flushed;
    return *this;

}
//overloading int
Log& Log::operator<<(int integer){
    fh<<integer;
    fh.flush();
    s= flushed;
    return *this;
}
//overloading double
Log& Log::operator<<(double d){
    fh<<d;
    fh.flush();
    s = flushed;
    return *this;
}
//returns string depending on which state the filehandler is in
std::string Log::return_state(){
    if(s==flushed){
        return "flushed";
    }
    else if(s==open){
        return "open";
    }
    else{
        return "closed";
    }
}