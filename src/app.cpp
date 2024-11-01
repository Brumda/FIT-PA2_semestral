#include "app.h"
#include "game.h"
#include <iostream>
#include <filesystem>

using namespace std;
#define doubleLine string(40, '=')

// Auxiliary function for handling wrong input
static void wrongInput() {
    if (cin.eof())
        throw runtime_error("EOF pressed");
    cout << "Invalid input." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Auxiliary function for loading files from directory
static vector<string> getFiles(const string &path) {
    vector<string> tmp;
    for (const auto &entry: filesystem::directory_iterator(path)) {
        if (entry.is_regular_file())
            tmp.push_back(entry.path().string());
    }
    return tmp;
}

void App::run(const std::string &mapsPath, const std::string &configsPath, const std::string &savesPath) {
    cout << doubleLine << "[Tower attack]" << doubleLine << endl;
    int choice;
    while (cin) {
        cout << "[1] New game \n[2] Load game" << endl;
        cin >> choice;
        if (cin.fail()) {
            wrongInput();
            continue;
        }
        if (choice == 1 || choice == 2)
            break;
        else wrongInput();
    }
    Game game(configsPath, savesPath);
    if (choice == 1)
        game.newGame(chooseFile(true, mapsPath));
    else if (choice == 2)
        game.loadGame(chooseFile(false, savesPath));

    cout << doubleLine << doubleLine << endl;
    cout << "Thanks for playing, see ya ♥" << endl;
}

string App::chooseFile(bool newGame, const std::string &filePath) {
    vector<string> files = getFiles(filePath);
    while (cin) {
        cout << "Choose " << (newGame ? "map" : "save file") << endl;
        for (size_t i = 1; i <= files.size(); ++i) {
            cout << "[" << i << "] " << files[i - 1].substr(filePath.rfind('/') + 1) << endl;
        }
        size_t choice;
        cin >> choice;
        if (cin.fail()) {
            wrongInput();
            continue;
        }
        if (choice > 0 && choice <= files.size())
            return files[choice - 1];
        else
            wrongInput();
    }

    return files[0];
}
