#ifndef CPMC_IO_HPP_INCLUDED
#define CPMC_IO_HPP_INCLUDED

#include <string>

namespace cpmc {

/**
 * Reads the whole content of the file at filePath
 * into a string, or exits with a message.
 */
std::string readFileOrExit(const std::string& filePath);

}  // namespace cpmc

#endif  // CPMC_IO_HPP_INCLUDED include guard
