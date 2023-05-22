#pragma once

#include <map>
#include <string>

class Config {
private:
    std::map<std::string, std::string> _options;
    std::string _filename;
public:
    Config(std::string filename);

    std::string operator[](std::string option);

    void update();
};