#ifndef CPMC_AST_EXPRESSION_PARSER_HPP_INCLUDED
#define CPMC_AST_EXPRESSION_PARSER_HPP_INCLUDED

#include <memory>
#include <set>

#include "ast/Expression.hpp"
#include "ast/ParsingContext.hpp"

namespace cpmc {
namespace ast {

/**
 * Parses CPM expressions.
 *
 * See Expression and ParsingContext.
 */
class ExpressionParser {
   public:
    static const std::set<std::string> validBinaryOperators;

   private:
    ParsingContext& context;

    /**
     * Caller must guarantee that
     * context.done() is false and context() == OPENING_BRACKET_TOKEN
     *
     * @throws ExpressionSyntaxError
     */
    std::unique_ptr<Expression> nextBracketClosedExpression();

    /**
     * Caller must guarantee that
     * context.done() is false and context() == INPUT_KEYWORD_TOKEN
     *
     * @throws ExpressionSyntaxError
     */
    std::unique_ptr<Expression> nextInputExpression();

    /**
     * Caller must guarantee that
     * context.done() is false.
     *
     * @throws ExpressionSyntaxError
     */
    std::unique_ptr<Expression> nextOperatorFreeExpression();

   public:
    ExpressionParser(ParsingContext& context);

    /**
     * Parses next expression (creating it in heap).
     *
     * @throws ExpressionSyntaxError on invalid expression.
     */
    std::unique_ptr<Expression> nextExpression();
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_EXPRESSION_PARSER_HPP_INCLUDED include guard
