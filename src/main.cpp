#include "app.h"
#include "mapLoading.h"
#include "libs/json.hpp"
#include <csignal>
#include <iostream>
#include <stdexcept>

using namespace std;

void signalHandler(int signum) {
    cout << "(" << signum << ")" << endl;
    throw runtime_error("CTRL + C pressed");
}

int main(int argc, char *argv[]) {
    cout << "\033[2J\033[H";
    std::string mapsPath;
    std::string configsPath;
    std::string saveFilesPath;
    if (argc > 1 && std::string(argv[1]) == "test") {
        std::string testPath;
        if(argc > 3) {
            testPath = argv[2];
            mapsPath = argv[3];
        }
        else {
            testPath = "./examples/tests/mapLoading";
            mapsPath = "./examples/";
        }
        auto mapTest = MapTest(testPath, mapsPath);
        mapTest.test();
        std::cout << "---------------------map tests passed---------------------" << std::endl;
        return 0;
    }
    if (argc < 4) {
        cout << "Not enough paths. Using default" << endl;
        mapsPath = "./examples/";
        configsPath = "./examples/config/";
        saveFilesPath = "./examples/saveFiles/";
    } else {
        mapsPath = argv[1];
        configsPath = argv[2];
        saveFilesPath = argv[3];
    }
    try {
        App app;
        app.run(mapsPath, configsPath, saveFilesPath);
        signal(SIGINT, signalHandler);
        return 0;

    } catch (const runtime_error &ex) {
        cerr << "Error: " << ex.what() << endl;
        return cin.eof() ? EXIT_SUCCESS : EXIT_FAILURE;
    } catch (const nlohmann::json::exception &e) {
        cerr << "Corrupted config" << endl;
        return 2;
    }
    catch (...) {
        cerr << "Something very wrong pls no veto" << endl;
        return 42;
    }
}