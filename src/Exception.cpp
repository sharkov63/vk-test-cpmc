#include "Exception.hpp"

namespace cpmc {

    /* Exception */
    
    Exception::Exception() = default;

    Exception::Exception(const std::string& message):
        message(message) {}

    const std::string& Exception::getMessage() const {
        return message;
    }

    /* CompilationException */

    CompilationException::CompilationException():
        Exception("Compilation failed.") {}

    CompilationException::CompilationException(const std::string& commandLine):
        Exception("Compilation with command line \"" + commandLine + "\" failed.") {}

    CompilationException::CompilationException(const std::string& commandLine,
                                               const std::string& error):
        Exception("Compilation with command line \"" + commandLine + "\" failed:\n" + error) {}
}
