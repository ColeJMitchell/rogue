//
// Created by cojmi on 3/13/2024.
//

#include "Configuration.h"

//Constructor using default file
Configuration::Configuration(){
    fileName="repo_lab3_mitchecj_jiany/default.txt";
    loadFromFile();
}
//Constructor using provided file location and name
Configuration::Configuration(const std::string& filepath, const std::string& filename){
    filePath=filepath;
    fileName = filename;
    loadFromFile();
}
//copy constructor
Configuration::Configuration(Configuration& obj){
    configMap = obj.configMap;
    filePath = obj.filePath;
    fileName = obj.fileName;
}

//copy assignment
Configuration& Configuration::operator=(Configuration& other){
    if(this!=&other){
        configMap = other.configMap;
        filePath = other.filePath;
        fileName = other.fileName;
    }
    return *this;
}

//Destructor
//Close the object
Configuration::~Configuration(){
    saveToFile();
}

//Load the file into a Map as a set of pairs of key and value
void Configuration::loadFromFile(){
    try{
        std::ifstream inputFile(filePath+fileName);
        if(!inputFile.is_open()){
            throw std::runtime_error("Fail to open the file "+filePath+fileName);
        }
        std::string key, value;
        while(inputFile >> key >> value){
            configMap[key] = value;
        }
        inputFile.close();
    }
    catch(std::exception& e){
        std::cerr << "Error for reading from file " << e.what() << std::endl;
    }
}

//Save the Map to the file
void Configuration::saveToFile(){
    std::ofstream outputFile(filePath+fileName);
    try{
        for(const auto& pair : configMap){
            outputFile<< pair.first << " " << pair.second <<std::endl;
        }
        outputFile.close();
    }
    catch(std::exception& e){
        std::cerr <<"Error for saving "<<e.what()<<std::endl;
    }
}

//Set a value for  given key in the Map
void Configuration::setValue(const std::string& key, const std::string& value){
    configMap[key] = value;
}

//Read a stored value given a key
//Return an empty string if the key does not exist
std::string Configuration::getValue(const std::string& key) const{
    auto it = configMap.find(key);
    return (it != configMap.end()) ? it->second : "Error: "+key+"not found";
}

//Refresh the Map:: delete current Map and reload from provided file
void Configuration::refreshMap(){
    configMap.clear();
    loadFromFile();
}
//Copy Map to a new file
//parameter newFilename includes file path and file name
void Configuration::copyMapToNewFile(const std::string& newFilename){
    std::ofstream outputFile(newFilename);
    try{
        for(const auto& pair : configMap){
            outputFile<< pair.first << " " << pair.second <<std::endl;
        }
        outputFile.close();
        std::cout << "Configuration saved to a new file " << newFilename <<std::endl;
    }
    catch(std::exception& e){
        std::cerr <<"Error for saving "<<e.what()<<std::endl;
    }

}
//Copy Map to new Configuration Object
//Receive a reference to a different Configuration object and store the contents
//of the Map.
void Configuration::copyMapToNewConfig(Configuration& obj){
    obj.configMap=this->configMap;
}

//set file path
void Configuration::setFilepath(std::string path){
    filePath=path;
}

//set file name
void Configuration::setFilename(std::string name){
    fileName=name;
}

//print the map
void Configuration::printMap(){
    for(auto& pair:configMap){
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

std::string Configuration::file_name() {
    return fileName;
}