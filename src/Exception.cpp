#include "Exception.hpp"

namespace cpmc {

/* Exception */

Exception::Exception() = default;

Exception::Exception(const std::string& message) : message(message) {}

const std::string& Exception::getMessage() const { return message; }

/* CompilationException */

CompilationException::CompilationException() : Exception("Compilation failed.") {}

CompilationException::CompilationException(const std::string& commandLine)
    : Exception("Compilation with command line \"" + commandLine + "\" failed.") {}

CompilationException::CompilationException(const std::string& commandLine, const std::string& error)
    : Exception("Compilation with command line \"" + commandLine + "\" failed:\n" + error) {}

/* InvalidTokenException */

InvalidTokenException::InvalidTokenException() : Exception("Found invalid token in source code.") {}

InvalidTokenException::InvalidTokenException(const std::string& token)
    : Exception("Found invalid token \"" + token + "\" in source code.") {}

InvalidTokenException::InvalidTokenException(const std::string& token,
                                             const std::string& expectedTokenMessage)
    : Exception("Found invalid token \"" + token + "\":\n" + expectedTokenMessage) {}

/* NoMoreTokensException */

NoMoreTokensException::NoMoreTokensException() : Exception() {}

/* SyntaxError */

SyntaxError::SyntaxError() : Exception("Syntax error.") {}

SyntaxError::SyntaxError(const std::string& error) : Exception("Syntax error:\n" + error) {}

/* ExpressionSyntaxError */

ExpressionSyntaxError::ExpressionSyntaxError() : SyntaxError("Invalid expression.") {}

ExpressionSyntaxError::ExpressionSyntaxError(const std::string& error)
    : SyntaxError("Invalid expression:\n" + error) {}

ExpressionSyntaxError::ExpressionSyntaxError(const std::string& expression,
                                             const std::string& error)
    : SyntaxError("Invalid expression \"" + expression + "\":\n" + error) {}

/* InstructionSyntaxError */

InstructionSyntaxError::InstructionSyntaxError() : SyntaxError("Invalid instruction.") {}

InstructionSyntaxError::InstructionSyntaxError(const std::string& error)
    : SyntaxError("Invalid instruction:\n" + error) {}

InstructionSyntaxError::InstructionSyntaxError(const std::string& instruction,
                                               const std::string& error)
    : SyntaxError("Invalid instruction \"" + instruction + "\":\n" + error) {}

}  // namespace cpmc
