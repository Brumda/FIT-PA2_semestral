#include <vector>
#include <memory>

/**
 * @class Map
 * @brief Class that represents the game board
 */
class Map {
private:

    struct towerPosition {
        bool empty;
        std::pair<int, int> position;

        towerPosition(const std::pair<int, int> &_position, bool _empty) : empty(_empty), position(_position) {}
    };                                          ///< auxiliary struct for keeping track where towers are and can be

public:
    int height = 0;                             ///< number of rows
    int width = 0;                              ///< number of columns
    std::pair<int, int> exit = {-1, -1}; ///< coordinates of the exit
    std::vector<std::vector<bool>> map;         ///< 2D array that represents walkable map fields. True walls, false empty tiles
    std::vector<std::pair<int, int>> entrances; ///< coordinates of entrances
    std::vector<towerPosition> towerSpawnAreas; ///< coordinates of possible tower areas

    Map() = default;

    explicit Map(const std::string &fileName);

    ~Map() = default;

    /**
     * @brief checks whether the tile is a valid move for the attacker
     * @param tile which tile to check
     * @param climb whether the attacker can climb on walls
     * @return true if the move is valid, false otherwise
     */
    bool validTile(const std::pair<int, int> &tile, bool climb) const;

    /**
     * @brief Loads map from a file
     * @throws runtime_error if the file is corrupted
     */
    void loadMap(const std::string &fileName);
};