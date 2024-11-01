#pragma once

/**
 * @class Stats
 * @brief Auxiliary class containing all the necessary attributes of an attacker that other classes might want to access and change
 */
class Stats {
public:
    int armor;        ///< by how much is the taken damage reduced
    int speed;        ///< tiles per round
    int damage;       ///< tiles per round
    int maxLives;     ///< maximum number of lives
    int currentLives; ///< current number of lives

    Stats(int _lives, int _armor, int _speed, int _damage) :
            armor(_armor), speed(_speed), damage(_damage), maxLives(_lives), currentLives(_lives) {}

    Stats(int _lives, int _armor, int _speed, int _damage, int _currentLives) :
            armor(_armor), speed(_speed), damage(_damage), maxLives(_lives), currentLives(_currentLives) {}
};
