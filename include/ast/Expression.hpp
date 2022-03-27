#ifndef CPMC_AST_EXPRESSION_HPP_INCLUDED
#define CPMC_AST_EXPRESSION_HPP_INCLUDED

#include "Token.hpp"

#include <memory>

namespace cpmc {
    namespace ast {
        
        /**
         * An expression in CPM language:
         * something which can be evaluated
         * to a specific value at runtime.
         */
        class Expression {
            public:
                Expression();
                virtual ~Expression();

                /**
                 * Converts this expression to a valid C++ expression.
                 */
                virtual std::string toCppExpression() const = 0;
        };


        /**
         * An expression which is a string, int or float literal.
         */
        class LiteralExpression : virtual public Expression {
            private:
                /**
                 * The literal itself.
                 */
                const std::string literal;

            public:
                LiteralExpression(const std::string& literal);
                virtual ~LiteralExpression();

                virtual std::string toCppExpression() const;
        };


        /**
         * An expression corresponding to single variable (or constant).
         */
        class IdentifierExpression : virtual public Expression {
            private:
                /**
                 * The identifier of a variable (or constant).
                 */
                const std::string identifier;

            public:
                IdentifierExpression(const std::string& identifier);
                virtual ~IdentifierExpression();

                virtual std::string toCppExpression() const;
        };


        /**
         * An expression of the form:
         * - input(<expression>)
         * - input()
         *
         * In the former case the expression is cast to string.
         * In the latter case the string argument is taken empty.
         */
        class InputExpression : virtual public Expression {
            private:
                const std::unique_ptr<Expression> argument;

            public:
                InputExpression();
                InputExpression(std::unique_ptr<Expression>& argument);
                virtual ~InputExpression();

                virtual std::string toCppExpression() const;
        };


        /**
         * An expression of type <expression1> + <expression2>
         * or <expression1> - <expression2>.
         */
        class OperationExpression : virtual public Expression {
            private:
                /**
                 * A symbol which denotes the binary operation.
                 * Currently, it is either '+' or '-'.
                 */
                const char operation;

                /**
                 * Left-hand side of the operation.
                 */
                const std::unique_ptr<Expression> lhs;       

                /**
                 * Right-hand side of the operation.
                 */
                const std::unique_ptr<Expression> rhs;       

            public:
                OperationExpression(char operation,
                                    std::unique_ptr<Expression>& lhs,
                                    std::unique_ptr<Expression>& rhs);
                virtual ~OperationExpression();

                virtual std::string toCppExpression() const;
        };
    }
}

#endif  // CPMC_AST_EXPRESSION_HPP_INCLUDED include guard
