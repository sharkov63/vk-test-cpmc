#ifndef CPMC_EXCEPTION_HPP_INCLUDED
#define CPMC_EXCEPTION_HPP_INCLUDED

#include <string>

#include "Token.hpp"

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
    CompilationException(const std::string& commandLine, const std::string& error);
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

/**
 * Internal exception which might be thrown inside Tokenizer class.
 */
class NoMoreTokensException : public Exception {
   public:
    NoMoreTokensException();
};

/**
 * An exception that may appear during parsing procedure.
 *
 * It means that the CPM source code contained a syntax error.
 */
class SyntaxError : public Exception {
   public:
    SyntaxError();
    SyntaxError(const std::string& error);
};

/**
 * An exception which may appear while parsing an expression
 * (see ExpressionParser).
 *
 * It means that the CPM source code contained an invalid expression.
 */
class ExpressionSyntaxError : public SyntaxError {
   public:
    ExpressionSyntaxError();
    ExpressionSyntaxError(const std::string& error);
    ExpressionSyntaxError(const std::string& expression, const std::string& error);
};

/**
 * An exception which may appear while parsing an instruction
 * (see InstructionParser).
 *
 * It means that the CPM source code contained an invalid instruction.
 */
class InstructionSyntaxError : public SyntaxError {
   public:
    InstructionSyntaxError();
    InstructionSyntaxError(const std::string& error);
    InstructionSyntaxError(const std::string& instruction, const std::string& error);
};

}  // namespace cpmc

#endif  // CPMC_EXCEPTION_HPP_INCLUDED include guard
