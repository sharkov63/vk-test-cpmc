#ifndef CPMC_AST_INSTRUCTION_PARSER_HPP_INCLUDED
#define CPMC_AST_INSTRUCTION_PARSER_HPP_INCLUDED

#include "ast/ExpressionParser.hpp"
#include "ast/Instruction.hpp"
#include "ast/ParsingContext.hpp"

namespace cpmc {
namespace ast {

/**
 * Parser CPM instructions.
 *
 * See Instruction nad ParsingContext.
 */
class InstructionParser {
   private:
    ParsingContext& context;

    ExpressionParser expressionParser;

   public:
    InstructionParser(ParsingContext& context);

    /**
     * Parses next Instruction (creating it in heap).
     *
     * Caller must guarantee that
     * context.done() == false.
     *
     * It is guaranteed to move context.pos to
     * at least one position forward.
     *
     * @throws InstructionSyntaxError on invalid Instruction.
     */
    std::unique_ptr<Instruction> nextInstruction();
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_INSTRUCTION_PARSER_HPP_INCLUDED include guard
