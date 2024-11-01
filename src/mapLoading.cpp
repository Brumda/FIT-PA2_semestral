#include "mapLoading.h"
#include "map.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <filesystem>

#define line string(50, '-') + '\n'

using namespace std;


MapTest::MapTest(string _testPath, std::string _correctPath) :
        testPath(std::move(_testPath)), correctPath(std::move(_correctPath)) {
    cout << line;
    for (const auto &entry: filesystem::directory_iterator(testPath)) {
        if (entry.is_regular_file())
            testFiles.push_back(entry.path().string());
    }
    for (const auto &entry: filesystem::directory_iterator(correctPath)) {
        if (entry.is_regular_file())
            correctFiles.push_back(entry.path().string());
    }
}

void MapTest::test() const {
    try {
        auto test = Map("some non-existent file");
        assert("Exception missing!" == nullptr);
    }
    catch (const ifstream::failure &e) {
        cerr << e.what() << endl;
    }
    catch (...) {
        assert("Wrong exception!" == nullptr);
    }
    for (const auto &file: testFiles) {
        try {
            cout << line;
            cout << file << endl;
            auto test = Map(file);
            assert("Exception missing!" == nullptr);
        }
        catch (const runtime_error &e) {
            cerr << '\t' << e.what() << endl;
        }
        catch (...) {
            assert("Different exception!" == nullptr);
        }
    }
    for (const auto &file: correctFiles) {
        try {
            cout << line;
            cout << file << endl;
            auto test = Map(file);
            cout << "correct" << endl;
        }
        catch (...) {
            assert("Exception thrown!" == nullptr);
        }
    }
}
