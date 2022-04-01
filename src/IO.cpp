#include "IO.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace cpmc {

std::string readFileOrExit(const std::string& filePath) {
    std::ifstream fin(filePath);
    if (!fin) {
        std::cout << "Could not read file at '" + filePath + "'." << std::endl;
        std::cout << "Exiting." << std::endl;
        exit(0);
    }
    std::ostringstream buf;
    buf << fin.rdbuf();
    return buf.str();
}

}  // namespace cpmc
