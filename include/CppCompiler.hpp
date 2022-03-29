#ifndef CPMC_CPP_COMPILER_HPP_INCLUDED
#define CPMC_CPP_COMPILER_HPP_INCLUDED

#include <string>

#include "CppSourceCode.hpp"

namespace cpmc {

/**
 * A C++ compiler wrapper, which can compile
 * CppSourceCode into a single executable file.
 */
class CppCompiler {
   private:
    /**
     * Path to the compiler.
     */
    const std::string compilerName;

    /**
     * Arguments passed to the compiler (not containing destination file).
     *
     * The arguments should be such that if destination file is added right
     * after, the compiler will compile source code from stdin into specified
     * destination file.
     *
     * See `compile` method for better understanding.
     */
    const std::string compileArgs;

   public:
    /**
     * Default compiler name and compile arguments are for GCC compiler.
     */
    static constexpr const char* const DEFAULT_COMPILER_NAME = "g++";
    static constexpr const char* const DEFAULT_COMPILE_ARGS = "-x c++ - -o";

    CppCompiler(const std::string& compilerName = DEFAULT_COMPILER_NAME,
                const std::string& compileArgs = DEFAULT_COMPILE_ARGS);

    /**
     * Compiles C++ source code `src` into executable file at `destination`.
     *
     * The actual executed compilation command line is built as follows:
     * $ <compilerName> <compileArgs> <destination>
     *
     * Example:
     * - compilerName = "g++";
     * - compileArgs  = "-x c++ - -o"
     * In this case the compilation command is:
     * $ g++ -x c++ - -o <destination>
     *
     * This method opens a process by creating a pipe (via popen/pclose),
     * passing the above-defined command line to the shell,
     * and passing `src` source code into pipe's standard input.
     *
     * The method waits until the compilation is finished (or returns with
     * non-zero exit status).
     *
     * @throws CompilationException if something went wrong during compilation
     * process.
     */
    void compile(const CppSourceCode& src,
                 const std::string& destination) const;
};

}  // namespace cpmc

#endif  // CPMC_CPP_COMPILER_HPP_INCLUDED include guard
