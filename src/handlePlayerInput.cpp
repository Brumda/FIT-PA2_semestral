#include "handlePlayerInput.h"
#include "attackerFactory.h"
#include <iostream>
#include <limits>

#define line string(35, '-')

using namespace std;

// Auxiliary function for handling wrong input
static void wrongInput() {
    if (cin.eof())
        throw runtime_error("EOF pressed");
    cout << "Invalid input." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

HandlePlayerInput::HandlePlayerInput(int *_spent, int *_playerMoney, AttackerFactory *_attackerFactory,
                                     AttackerEffectsFactory *_attackerEffectsFactory,
                                     std::map<int, std::queue<std::shared_ptr<Attacker>>> *_attackersQueue) :
        spent(_spent),
        playerMoney(_playerMoney),
        attackerFactory(_attackerFactory),
        attackerEffectsFactory(_attackerEffectsFactory),
        attackersQueue(_attackersQueue) {}


bool HandlePlayerInput::chooseEntry(size_t &entrance) const {
    size_t i{};
    while (cin) {
        bool first = true;
        cout << "Choose entrance: {";
        for (i = 1; i <= mapEntrances->size(); ++i) {
            if (first) {
                first = false;
                cout << i;
            } else cout << ", " << i;
        }
        cout << "}" << endl;
        cout << "End turn: [" << i << "] " << endl;
        cin >> entrance;
        if (cin.fail()) {
            wrongInput();
            continue;
        }
        if (entrance > 0 && entrance <= mapEntrances->size() + 1)
            break;
        else
            wrongInput();
    }
    return entrance != i;
}

bool HandlePlayerInput::chooseAttacker(size_t &entrance) {
    while (cin) {
        cout << "Chosen entrance: [" << entrance << "]" << endl;
        cout << "Money left: " << *playerMoney << "$" << endl;
        cout << line << endl;
        cout << "Choose attacker:" << endl;
        size_t i = 0;
        for (const auto &attacker: attackerFactory->getPossibilities()) {
            cout << "[" << ++i << "] " << attacker << " – price: [" << attackerFactory->getPrice(attacker) << "$]"
                 << endl;
        }
        cout << "[" << ++i << "] " << "choose different entrance" << endl;
        size_t chosenAttacker{};
        cin >> chosenAttacker;
        if (cin.fail()) {
            wrongInput();
            continue;
        }
        if (chosenAttacker == i) {
            if (!chooseEntry(entrance)) return false;
            chooseAttacker(entrance);
        }
        if (chosenAttacker > 0 && chosenAttacker <= attackerFactory->getPossibilities().size()) {
            auto name = attackerFactory->getPossibilities()[chosenAttacker - 1];
            int price = attackerFactory->getPrice(name);
            if (*playerMoney >= price) {
                *playerMoney -= price;
                *spent += price;

                auto attacker = attackerFactory->makeAttacker(name,
                                                              (*mapEntrances)[entrance - 1]);
                set<size_t> applied;
                while (true) {
                    auto effect = chooseEffect(applied);
                    if (!effect) break;
                    attacker->addEffect(std::move(effect));
                }
                (*attackersQueue)[entrance - 1].push(std::move(attacker));
                break;
            } else cout << "You dont have enough money" << endl;
        } else
            wrongInput();
    }
    return true;
}

unique_ptr<AttackerEffect> HandlePlayerInput::chooseEffect(set<size_t> &applied) {
    while (cin) {
        cout << line << "\nMoney left: " << *playerMoney << "$\n" << "Choose effect:" << endl;
        size_t i = 0;
        for (const auto &effect: attackerEffectsFactory->getPossibilities())
            cout << "[" << ++i << "] " << effect << " – price: [" << attackerEffectsFactory->getPrice(effect) << "$]"
                 << endl;

        cout << "[" << ++i << "] " << "none" << endl;
        size_t chosenEffect;
        cin >> chosenEffect;
        if (cin.fail()) {
            wrongInput();
            continue;
        }
        if (chosenEffect == i) return nullptr;

        if (chosenEffect > 0 && chosenEffect <= attackerEffectsFactory->getPossibilities().size()) {
            auto name = attackerEffectsFactory->getPossibilities()[chosenEffect - 1];
            int price = attackerEffectsFactory->getPrice(name);
            if (applied.count(chosenEffect)) {
                cout << "effect already applied" << endl;
                continue;
            }
            if (*playerMoney >= price) {
                *playerMoney -= price;
                *spent += price;
                applied.insert(chosenEffect);
                return attackerEffectsFactory->makeAttackerEffect(
                        attackerEffectsFactory->getPossibilities()[chosenEffect - 1]);
            } else cout << "You dont have enough money" << endl;
        } else
            wrongInput();
    }
    return nullptr;
}

bool HandlePlayerInput::saveGame() {
    size_t choice{};
    while (cin) {
        cout << "Wanna save the game?" << endl;
        cout << "[" << 1 << "] " << "Yes" << endl;
        cout << "[" << 2 << "] " << "No" << endl;
        cin >> choice;
        if (cin.fail()) {
            wrongInput();
            continue;
        }
        if (choice == 1 || choice == 2)
            break;
        else
            wrongInput();
    }
    return choice == 1;
}

bool HandlePlayerInput::exitGame() {
    size_t choice{};
    while (cin) {
        cout << "Wanna exit the game?" << endl;
        cout << "[" << 1 << "] " << "Yes" << endl;
        cout << "[" << 2 << "] " << "No" << endl;
        cin >> choice;
        if (cin.fail()) {
            wrongInput();
            continue;
        }
        if (choice == 1 || choice == 2)
            break;
        else
            wrongInput();
    }
    return choice == 1;
}
