#include "ast/ProgramParser.hpp"

namespace cpmc {
namespace ast {

ProgramParser::ProgramParser(ParsingContext& context)
    : context(context), instructionParser(InstructionParser(context)) {}

Program ProgramParser::parse() {
    // TODO
    throw;
}

}  // namespace ast
}  // namespace cpmc
