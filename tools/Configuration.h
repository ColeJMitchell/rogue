//
// Created by cojmi on 3/13/2024.
//

#ifndef REPO_LAB3_MITCHECJ_JIANGY_CONFIGURATION_H
#define REPO_LAB3_MITCHECJ_JIANGY_CONFIGURATION_H
#include <iostream>
#include <string>
#include <map>
#include <fstream>



class Configuration{
public:
    Configuration();
    explicit Configuration(const std::string& filepath, const std::string& filename);
    Configuration(Configuration& obj);
    Configuration& operator=(Configuration& other);
    ~Configuration();
    std::string getValue(const std::string& key) const;
    std :: string file_name();
    void setValue(const std::string& key, const std::string& value);
    void saveToFile();
    void refreshMap();
    void copyMapToNewFile(const std::string& newFilename);
    void copyMapToNewConfig(Configuration& obj);
    void setFilepath(std::string path);
    void setFilename(std::string name);
    void printMap();
private:
    std::map<std::string,std::string> configMap;
    std::string filePath;
    std::string fileName;
    void loadFromFile();
};



#endif //REPO_LAB3_MITCHECJ_JIANGY_CONFIGURATION_H