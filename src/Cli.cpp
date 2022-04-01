#include "Cli.hpp"

#include <iostream>

namespace cpmc {

/* CliArgResult */
CliArgResult::CliArgResult(const std::string& sourceFileName, const std::string& targetFileName)
    : sourceFileName(sourceFileName), targetFileName(targetFileName) {}

/* CliArgParser */

void CliArgParser::printHelpAndExit() {
    std::cout << "CPMC (C+- compiler)." << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "$ cpmc <path_to_source> <path_to_target>" << std::endl;
    exit(0);
}

CliArgResult CliArgParser::parse(const std::vector<std::string>& args) {
    if (args.size() <= 1 || args[1] == "--help") printHelpAndExit();
    if (args.size() < 3) {
        std::cout << "Invalid arguments: expected target file path after source path." << std::endl;
        printHelpAndExit();
    }
    return CliArgResult(args[1], args[2]);
}

CliArgParser::CliArgParser() = default;

CliArgResult CliArgParser::parse(int argc, const char** argv) {
    std::vector<std::string> args(argc);
    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }
    return parse(args);
}

}  // namespace cpmc
