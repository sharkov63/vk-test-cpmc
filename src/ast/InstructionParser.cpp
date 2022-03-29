#include "ast/InstructionParser.hpp"

namespace cpmc {
namespace ast {

InstructionParser::InstructionParser(ParsingContext& context)
    : context(context), expressionParser(ExpressionParser(context)) {}

std::unique_ptr<Instruction> InstructionParser::nextInstruction() {
    // TODO
    throw;
}

}  // namespace ast
}  // namespace cpmc
