#pragma once

#include <vector>
#include <string>
/**
 * @class App
 * @brief Class that handles first interaction with user. Here is determined from where to load the game or start a new one
 */
class App {
public:
    /**
     * @brief Based on user input starts new game or loads save file
     * @param mapsPath path to the maps directory
     * @param configsPath path to the configs directory
     * @param savesPath path to the save files directory
     */
    void run(const std::string &mapsPath, const std::string &configsPath, const std::string &savesPath);
    /**
     * @brief Auxiliary method for choosing which file to use via user input
     * @param newGame whether the user wants to start a new game
     * @param filePath path to the corresponding directory
     * @return Name of the file
     */
    std::string chooseFile(bool newGame, const std::string &filePath);
};
