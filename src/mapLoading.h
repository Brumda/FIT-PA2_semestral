#pragma once

#include<string>
#include<vector>

/**
 * @class MapTest
 * @brief Auxiliary class for testing map files
 */
class MapTest {
    std::string testPath;                  ///< path to the wrong files
    std::string correctPath;               ///< path to the correct files
    std::vector<std::string> testFiles;    ///< files that are wrong and should fail the loading
    std::vector<std::string> correctFiles; ///< files that are correct and shouldn't fail the loading
public:
    explicit MapTest(std::string _testPath, std::string _correctPath);

    /**
     * @brief Tests all the files
     */
    void test() const;
};