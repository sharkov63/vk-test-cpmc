#ifndef CPMC_EXCEPTION_HPP_INCLUDED
#define CPMC_EXCEPTION_HPP_INCLUDED

#include "Token.hpp"

#include <string>

namespace cpmc {

    /**
     * Generic class for all exceptions in cpmc.
     */
    class Exception {
        private:
            /**
             * The message explaining this exception.
             */
            std::string message;

        public:
            Exception();
            Exception(const std::string& message);

            /**
             * @return the message explaining this exception.
             */
            const std::string& getMessage() const;
    };

    /**
     * Exception thrown in `compile` method of CppCompiler class.
     */
    class CompilationException : public Exception {
        public:
            CompilationException();
            CompilationException(const std::string& commandLine);
            CompilationException(const std::string& commandLine,
                                 const std::string& error);
    };

    /**
     * Exception throws in `tokenize` method of Tokenizer class.
     */
    class InvalidTokenException : public Exception {
        public:
            InvalidTokenException();
            InvalidTokenException(const std::string& token);
            InvalidTokenException(const std::string& token, const std::string& expectedTokenMessage);
    };
}

#endif // CPMC_EXCEPTION_HPP_INCLUDED include guard
