#include "Generator.h"


auto Generator::initWordsToDraw(const int &num) -> void {
    auto fileToR = std::fstream(files[num]);
    auto line = std::string();

    while (std::getline(fileToR, line)) {
        wordsToDraw.push_back(line);
    }
}
