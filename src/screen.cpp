#include "screen.h"
#include <iostream>

using namespace std;
#define line string(35, '-')
#define doubleLine string(40, '=')

Screen::Screen(const int *lives, const int *round, int maxRound, int baseLives, const int *playerMoney,
               const std::vector<std::unique_ptr<Tower>> *towers, const std::vector<std::shared_ptr<Attacker>> *attackers) :
        lives(lives), round(round), maxRound(maxRound),
        baseLives(baseLives), playerMoney(playerMoney),
        towers(towers), attackers(attackers) {}

void Screen::redraw() const {
    vector<vector<char>> buffer(map->height + 2, vector<char>(map->width + 3, ' '));

    for (int h = 0; h < map->height; ++h)
        for (int w = 0; w < map->width; ++w)
            buffer[1 + h][3 + w] = map->map[h][w] ? 'X' : ' ';

    for (const auto &towerPosition: map->towerSpawnAreas) {
        if(towerPosition.empty)
            buffer[1 + towerPosition.position.first][3 + towerPosition.position.second] = '@';
    }
    int num = 0;
    for (const auto &coords: map->entrances) {
        buffer[1 + coords.first][0 + coords.second] = to_string(++num)[0];
        buffer[1 + coords.first][1 + coords.second] = '.';
        buffer[1 + coords.first][3 + coords.second] = '=';
    }

    buffer[1 + map->exit.first][3 + map->exit.second] = '>';

    for (const auto &tower: *towers)
        buffer[1 + tower->getCoordinates().first][3 + tower->getCoordinates().second] = tower->getSymbol();

    for (const auto &attacker: *attackers)
        buffer[1 + attacker->getCoordinates().first][3 + attacker->getCoordinates().second] = attacker->getSymbol();

    cout << "\033[2J\033[H";
    cout << doubleLine << "[Tower attack]" << doubleLine << endl;
    for (const auto &row: buffer) {
        for (const auto &c: row) {
            cout << c;
        }
        cout << "\n";
    }
    if (*round > maxRound)
        cout << "Round: " << maxRound << "/" << maxRound << endl;
    else cout << "Round: " << *round << "/" << maxRound << endl;
    cout << "Lives: " << *lives << "/" << baseLives << " ♥" << endl;
    cout << "Money: " << *playerMoney << "$" << endl;
    if (*lives > 0 && *round <= maxRound)
        cout << line << endl;
}

void Screen::winScreen(int spent) const {
    cout << line << " You won! " << line << endl;
    cout << "Every one loves you, you are a hero and your mama is proud of you ♥" << endl;
    cout << "It took you " << *round << " rounds out of " << maxRound << " and you have spent " << spent
         << "$ out of the tax payers pockets.\nWorth it." << endl;
}

void Screen::loseScreen(int spent) const {
    cout << line << " You lost :( " << line << endl;
    cout << "You couldn't breach enemy lines in time. Everyone thinks you're a looser,\nyour parents disowned you. "
            "You wasted " << spent << "$ out of tax payers pockets\nand only did " << baseLives - *lives
         << " damage out of " << baseLives << "\nYou should go cry into the bathroom – the only place"
                                              " the angry mob won't search" << endl;
}
