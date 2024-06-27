#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <fstream>
#include <vector>
#include <fstream>

class Generator {
public:
    const std::string file1 = "../assets/animal_words.txt";
    const std::string file2 = "../assets/adjectives_words.txt";
    const std::string file3 = "../assets/food_words.txt";
    const std::array<std::string, 3> files = { file1, file2, file3 };

    std::vector<std::string> wordsToDraw;

    auto initWordsToDraw(int const& num) -> void;

};


