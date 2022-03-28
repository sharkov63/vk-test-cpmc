#include "ast/ExpressionParser.hpp"

#include "Exception.hpp"
#include "Debug.hpp"

namespace cpmc {
    namespace ast {

        const std::set<std::string> ExpressionParser::validBinaryOperators = {
            "+",
            "-",
        };

        ExpressionParser::ExpressionParser(ParsingContext& context):
            context(context) {}

        std::unique_ptr<Expression> ExpressionParser::nextBracketClosedExpression() {
            size_t initialPosition = context.position();

            context++;
            std::unique_ptr<Expression> result = nextExpression();

            if (context.done() || context() != CLOSING_BRACKET_TOKEN) {
                // no matching bracket
                throw ExpressionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                            "Expected closing bracket \")\", found \"" + context().getValue() + "\".");
            }

            context++;
            return result;
        }

        std::unique_ptr<Expression> ExpressionParser::nextInputExpression() {
            size_t initialPosition = context.position();

            context++;

            if (context.done() || context() != OPENING_BRACKET_TOKEN) {
                throw ExpressionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                            "Expected opening bracket \"(\" after \"input\" keyword, found \"" + context().getValue() + "\".");
            }

            size_t bracketPosition = context.position();
            if (bracketPosition + 1 >= context.size()) {
                throw ExpressionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                            "Expected an expression or closing bracket \")\" after opening bracket \"(\", found EOF.");
            }

            if (context[bracketPosition + 1] == CLOSING_BRACKET_TOKEN) {
                // input()

                context += 2;

                std::unique_ptr<Expression> result(new InputExpression());
                return result;
            }

            // input(<expression>)
            std::unique_ptr<Expression> argument = nextBracketClosedExpression();
            std::unique_ptr<Expression> result(new InputExpression(argument));
            return result;
        }

        std::unique_ptr<Expression> ExpressionParser::nextOperatorFreeExpression() {
            Token nextToken = context();
            TokenType type = nextToken.getType();

            if (type == TokenType::IDENTIFIER) {
                // expression consists of a single identifier
                std::unique_ptr<Expression> result(new IdentifierExpression(context().getValue()));
                context++;
                return result;
            }

            if (type == TokenType::DELIMITER) {
                if (nextToken == OPENING_BRACKET_TOKEN) {
                    // (<expression>)
                    return nextBracketClosedExpression();
                }

                throw ExpressionSyntaxError(nextToken.getValue(),
                                            "Expected expression.");
            }

            if (type == TokenType::KEYWORD) {
                if (nextToken.getValue() == "input") {
                    // input(<expression>) or input()
                    return nextInputExpression();
                }

                throw ExpressionSyntaxError(nextToken.getValue(),
                                            "Expected expression, found keyword \"" + nextToken.getValue() + "\".");
            }

            if (type == TokenType::STRING_LITERAL) {
                // expression consists of a single string literal
                std::unique_ptr<Expression> result(new StringLiteralExpression(context().getValue()));
                context++;
                return result;
            }

            if (type == TokenType::INT_LITERAL) {
                // expression consists of a single int literal
                std::unique_ptr<Expression> result(new IntLiteralExpression(context().getValue()));
                context++;
                return result;
            }

            if (type == TokenType::FLOAT_LITERAL) {
                // expression consists of a single float literal
                std::unique_ptr<Expression> result(new FloatLiteralExpression(context().getValue()));
                context++;
                return result;
            }

            throw ExpressionSyntaxError(nextToken.getValue(),
                                        "Expected expression, found \"" + nextToken.getValue() + "\".");
        }

        std::unique_ptr<Expression> ExpressionParser::nextExpression() {
            if (context.done()) {
                throw ExpressionSyntaxError("Expected expression, found EOF.");
            }

            size_t initialPosition = context.position();
            std::unique_ptr<Expression> lhs = nextOperatorFreeExpression();

            if (!context.done() && context().getType() == TokenType::OPERATOR) {
                // a binary operation is taking place
                Token operationToken = context();

                if (validBinaryOperators.find(operationToken.getValue()) == validBinaryOperators.end()) {
                    throw ExpressionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                                "Invalid binary operator \"" + operationToken.getValue() + "\".");
                }

                std::string operation = operationToken.getValue();
                context++;
                std::unique_ptr<Expression> rhs = nextExpression();
                std::unique_ptr<Expression> result(new OperationExpression(operation, lhs, rhs));
                return result;
            }

            // no binary operation
            return lhs;
        }
    }
}
