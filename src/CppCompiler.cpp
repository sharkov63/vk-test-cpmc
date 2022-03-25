#include "CppCompiler.hpp"
#include "Exception.hpp"

#include <stdio.h>
#include <errno.h>
#include <string.h>

namespace cpmc {

    CppCompiler::CppCompiler(const std::string& compilerName,
                             const std::string& compileArgs):
        compilerName(compilerName),
        compileArgs(compileArgs) {}

    void CppCompiler::compile(const CppSourceCode& src, const std::string& destination) const {
        std::string commandLine = compilerName + " " + compileArgs + " " + destination;

        // open pipe
        FILE* pipe = popen(commandLine.c_str(), "w"); 
        if (pipe == nullptr) {
            std::string error = std::string("Could not open pipe:\n") + strerror(errno);
            throw CompilationException(commandLine, error);
        }
        // pipe opened successfully
        
        int writeResult = fprintf(pipe, "%s", src.getContent().c_str()); // write source code to pipe stdin
        if (writeResult < 0) {
            pclose(pipe);
            std::string error = "Could not write to opened pipe's standard input.";
            throw CompilationException(commandLine, error);
        }
        // written source code successfully

        int exitStatus = pclose(pipe); // wait for process to finish

        if (exitStatus != 0) {
            std::string error = "Compiler returns non-zero exit code (" + std::to_string(exitStatus) + "):\n" + strerror(errno);
            throw CompilationException(commandLine, error);
        }
    }
}
