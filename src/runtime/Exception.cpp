#ifndef CPMC_EXCEPTION_RUNTIME_INCLUDED
#define CPMC_EXCEPTION_RUNTIME_INCLUDED

/** Beginning of Exception.cpp */

/**
 * This CPP file will be inserted in
 * every translated-into-CPP CPM code,
 * so it combines both declaration
 * and implementation and does not have
 * corresponding header file.
 *
 * Also, in order to not depend on C++11
 * standard, it does not utilize
 * stuff like std::unique_ptr and etc.
 */

#include <string>

namespace cpmc {
namespace runtime {

class CPMRuntimeError {
   private:
    std::string message;

   public:
    CPMRuntimeError() : message("Runtime error.") {}
    CPMRuntimeError(const std::string& message) : message("Runtime error:\n" + message) {}
};

}  // namespace runtime
}  // namespace cpmc

/** End of Exception.cpp */

#endif  // CPMC_EXCEPTION_RUNTIME_INCLUDED include guard
