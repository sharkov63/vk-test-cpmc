#ifndef CPMC_CLI_HPP_INCLUDED
#define CPMC_CLI_HPP_INCLUDED

#include <string>
#include <vector>

namespace cpmc {

/**
 * The result of CLI arguments parsing.
 */
class CliArgResult {
   public:
    const std::string sourceFileName;
    const std::string targetFileName;

    CliArgResult(const std::string& sourceFileName, const std::string& targetFileName);
};

/**
 * CLI handler.
 */
class CliArgParser {
   private:
    void printHelpAndExit();

    CliArgResult parse(const std::vector<std::string>& args);

   public:
    CliArgParser();

    /**
     * Parses given arguments.
     *
     * On invalid arguments,
     * prints help message and quits.
     */
    CliArgResult parse(int argc, const char** argv);
};

}  // namespace cpmc

#endif  // CPMC_CLI_HPP_INCLUDED include guard
