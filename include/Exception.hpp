#ifndef CPMC_EXCEPTION_HPP_INCLUDED
#define CPMC_EXCEPTION_HPP_INCLUDED

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
}

#endif // CPMC_EXCEPTION_HPP_INCLUDED include guard
