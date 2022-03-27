#ifndef CPMC_AST_EXPRESSION_PARSER_HPP_INCLUDED
#define CPMC_AST_EXPRESSION_PARSER_HPP_INCLUDED

#include "ast/Expression.hpp"
#include "ast/ParsingContext.hpp"

#include <memory>

namespace cpmc {
    namespace ast {

        /**
         * Parses CPM expressions.
         *
         * See Expression and ParsingContext.
         */
        class ExpressionParser {
            private:
                const ParsingContext& context;

            public:
                ExpressionParser(const ParsingContext& context);

                /**
                 * Parses next expression.
                 *
                 * @throws ExpressionSyntaxError on invalid expression.
                 */
                std::unique_ptr<Expression> nextExpression();
        };
    }
}

#endif  // CPMC_AST_EXPRESSION_PARSER_HPP_INCLUDED include guard
