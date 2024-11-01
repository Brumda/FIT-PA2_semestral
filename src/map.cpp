#include "map.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;
constexpr const char FIELD_EMPTY = ' ';
constexpr const char FIELD_WALL = '#';
constexpr const char FIELD_EXIT = '>';
constexpr const char FIELD_ENTRANCE = '=';
constexpr const char TOWER_PLATFORM = '@';

Map::Map(const string &fileName) { Map::loadMap(fileName); }


void Map::loadMap(const string &fileName) {
    fstream fileIn(fileName, ifstream::in);
    fileIn.exceptions(ios::badbit);
    if (!fileIn)
        throw ifstream::failure("File does not exist: '" + fileName + "'");

    if (!(fileIn >> skipws >> width >> height >> noskipws)) {
        throw runtime_error("Unable to read dimension of map.");
    }
    if (fileIn.get() != '\n')
        throw runtime_error("New line missing after dimensions");
    map = vector<vector<bool>>(height, vector<bool>(width, false));

    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            int c = fileIn.get();
            switch (c) {
                case FIELD_WALL:
                    map[h][w] = true;
                    break;
                case FIELD_ENTRANCE:
                    entrances.emplace_back(h, w);
                    break;
                case TOWER_PLATFORM:
                    map[h][w] = true;
                    towerSpawnAreas.emplace_back(make_pair(h, w), true);
                    break;
                case FIELD_EXIT:
                    exit = {h, w};
                    break;
                case FIELD_EMPTY:
                    break;
                default:
                    throw runtime_error("Map contains unsupported characters");
            }
        }
        /// Checks if the map has walls all around
        if (!map[h][width - 1] && exit != make_pair(h, width - 1))
            throw runtime_error("Right border wall missing in map");

        if (!map[h][0] && entrances.back() != make_pair(h, 0))
            throw runtime_error("Left border wall missing in map");

        if (h == 0 && !all_of(map[h].begin(), map[h].end(), [](bool value) { return value; }))
            throw runtime_error("Top of border wall missing in map");

        if (h == height - 1 && !all_of(map[h].begin(), map[h].end(), [](bool value) { return value; }))
            throw runtime_error("Bottom of border wall missing in map");

        if (fileIn.get() != '\n')
            throw runtime_error("New line missing in map");
    }
    if (entrances.empty())
        throw runtime_error("No entrance to the map");
    if (exit.first < 0)
        throw runtime_error("No exit out of the map");
    fileIn.close();
}

bool Map::validTile(const pair<int, int> &tile, bool climb) const {
    int x = tile.second;
    int y = tile.first;
    if (x <= 0 || x >= width) return false;
    if (y <= 0 || y >= height) return false;
    if (map[y][x] && !climb) return false;
    return true;
}

