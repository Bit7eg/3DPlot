#include "Config.h"

#include <fstream>

Config::Config(std::string filename) {
    this->_filename = filename;
    this->update();
}

std::string Config::operator[](std::string option) {
    return this->_options[option];
}

void Config::update() {
    this->_options.clear();

    std::ifstream config_file(this->_filename);
    if (!config_file.is_open() || config_file.fail())
    {
        return;
    }
    
    std::string key, value;
    while (!config_file.eof())
    {
        config_file>>key;
        std::getline(config_file, value);
        this->_options[key] = value;
    }
    
    config_file.close();
}