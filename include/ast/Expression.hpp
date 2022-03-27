#ifndef CPMC_AST_EXPRESSION_HPP_INCLUDED
#define CPMC_AST_EXPRESSION_HPP_INCLUDED

#include "Token.hpp"

#include <memory>

namespace cpmc {
    namespace ast {

        /**
         * Possible types of Expression.
         */
        enum ExpressionType {
            STRING_LITERAL,      /// A string literal.
            INT_LITERAL,         /// An int literal.
            FLOAT_LITERAL,       /// A float literal.
            IDENTIFIER,          /// An identifier (a name of a variable or a constant).
            INPUT,               /// An expression of type input(<expression>) or input().
            OPERATION,           /// A binary operation: <expression><op><expression> where <op> is '+' or '-'.
        };
        
        /**
         * An expression in CPM language:
         * something which can be evaluated
         * to a specific value at runtime.
         *
         * Note that expression cannot be empty!
         */
        class Expression {
            protected:
                /**
                 * The type of expression.
                 *
                 * MUST always match the derived class.
                 */
                const ExpressionType type;

                Expression(const ExpressionType& type);

            public:
                virtual ~Expression();

                ExpressionType getType() const;

                /**
                 * Converts this expression to a valid C++ expression.
                 */
                virtual std::string toCppExpression() const = 0;

                /**
                 * Compares to expressions.
                 *
                 * Needed mostly for unit testing.
                 *
                 * N.B.: stack-unsafe, uses a lot of recursion!
                 */
                virtual bool operator==(const Expression& other) const = 0;
        };


        /**
         * An expression which is a string, int or float literal.
         */
        class LiteralExpression : public Expression {
            protected:
                /**
                 * The literal itself.
                 */
                const std::string literal;

                LiteralExpression(ExpressionType type, const std::string& literal);

            public:
                virtual ~LiteralExpression() override;

                virtual std::string toCppExpression() const override;

                virtual bool operator==(const Expression& other) const override final;
        };


        /**
         * String literal.
         */
        class StringLiteralExpression : public LiteralExpression {
            public:
                StringLiteralExpression(const std::string& litreal);
                virtual ~StringLiteralExpression() override;
        };


        /**
         * Int literal.
         */
        class IntLiteralExpression : public LiteralExpression {
            public:
                IntLiteralExpression(const std::string& literal);
                virtual ~IntLiteralExpression() override;
        };


        /**
         * Float literal.
         */
        class FloatLiteralExpression : public LiteralExpression {
            public:
                FloatLiteralExpression(const std::string& literal);
                virtual ~FloatLiteralExpression() override;
        };


        /**
         * An expression corresponding to single variable (or constant).
         */
        class IdentifierExpression : public Expression {
            protected:
                /**
                 * The identifier of a variable (or constant).
                 */
                const std::string identifier;

            public:
                IdentifierExpression(const std::string& identifier);
                virtual ~IdentifierExpression() override;

                virtual std::string toCppExpression() const override;

                virtual bool operator==(const Expression& other) const override;
        };


        /**
         * An expression of the form:
         * - input(<expression>)
         * - input()
         *
         * In the former case the expression is cast to string.
         * In the latter case the string argument is taken empty.
         */
        class InputExpression : public Expression {
            protected:
                const std::unique_ptr<Expression> argument;

            public:
                InputExpression();
                InputExpression(std::unique_ptr<Expression>& argument);
                virtual ~InputExpression() override;

                virtual std::string toCppExpression() const override;

                virtual bool operator==(const Expression& other) const override;
        };


        /**
         * An expression of type <expression1> + <expression2>
         * or <expression1> - <expression2>.
         */
        class OperationExpression : public Expression {
            protected:
                /**
                 * A string which denotes the binary operation.
                 * Currently, it is either '+' or '-'.
                 */
                const std::string operation;

                /**
                 * Left-hand side of the operation.
                 */
                const std::unique_ptr<Expression> lhs;       

                /**
                 * Right-hand side of the operation.
                 */
                const std::unique_ptr<Expression> rhs;       

            public:
                OperationExpression(const std::string operation,
                                    std::unique_ptr<Expression>& lhs,
                                    std::unique_ptr<Expression>& rhs);
                virtual ~OperationExpression() override;

                virtual std::string toCppExpression() const override;

                virtual bool operator==(const Expression& other) const override;
        };
    }
}

#endif  // CPMC_AST_EXPRESSION_HPP_INCLUDED include guard
