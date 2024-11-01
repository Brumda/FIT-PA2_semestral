#include "configLoader.h"
#include <fstream>
#include <iostream>

using namespace std;

ConfigLoader::ConfigLoader(const std::string &configFile) {
    using json = nlohmann::json;
    std::ifstream f(configFile);
    try {
        data = json::parse(f);
    }
    catch (const json::exception &e) {
        std::cout << "Something went wrong with loading config file: " <<
                  configFile.substr(configFile.rfind('/') + 1) <<
                  ". Default values may be used." << std::endl;
    }
    for (auto it = data.begin(); it != data.end(); ++it) {
        possibilities.push_back(it.key());
    }
}