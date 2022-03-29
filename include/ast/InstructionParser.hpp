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

    /**
     * Parses next Expression via expressionParser.
     * The difference is that it wraps
     * ExpressionSyntaxError into InstructionSyntaxError.
     *
     * @throws InstructionSyntaxError.
     */
    std::unique_ptr<Expression> nextExpression();

    /**
     * Parses next Expression via expressionParser
     * and turns it into an empty instruction.
     *
     * It also reads a semicolon after the expression.
     *
     * @throws InstructionSyntaxError.
     */
    std::unique_ptr<Instruction> nextExpressionAsEmptyInstruction();

    /**
     * Parses next Definition.
     *
     * Caller must guarantee that
     * context.done() == false
     * and context() is either VAL_KEYWORD_TOKEN or VAR_KEYWORD_TOKEN.
     *
     * @throws InstructionSyntaxError.
     */
    std::unique_ptr<Instruction> nextDefinition();

    /**
     * Parses next Printing.
     *
     * Caller must guarantee that
     * context.done() == false
     * and context() is PRINT_KEYWORD_TOKEN.
     *
     * @throws InstructionSyntaxError.
     */
    std::unique_ptr<Instruction> nextPrinting();

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
