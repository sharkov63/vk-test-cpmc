#ifndef CPMC_AST_PROGRAM_PARSER_HPP_INCLUDED
#define CPMC_AST_PROGRAM_PARSER_HPP_INCLUDED

#include "ast/InstructionParser.hpp"
#include "ast/ParsingContext.hpp"
#include "ast/Program.hpp"

namespace cpmc {
namespace ast {

/**
 * Parses a CPM program.
 *
 * See Program and ParsingContext.
 */
class ProgramParser {
   private:
    ParsingContext& context;

    InstructionParser instructionParser;

   public:
    ProgramParser(ParsingContext& context);

    /**
     * Parses a Program from given context.
     *
     * @throws SyntaxError.
     */
    Program parse();
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_PROGRAM_PARSER_HPP_INCLUDED include guard
