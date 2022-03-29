#include "ast/InstructionParser.hpp"

#include "Exception.hpp"

namespace cpmc {
namespace ast {

InstructionParser::InstructionParser(ParsingContext& context)
    : context(context), expressionParser(ExpressionParser(context)) {}

std::unique_ptr<Expression> InstructionParser::nextExpression() {
    std::unique_ptr<Expression> expression;
    try {
        expression = expressionParser.nextExpression();
    } catch (const ExpressionSyntaxError& e) {
        throw InstructionSyntaxError(e.getMessage());
    }
    return expression;
}

std::unique_ptr<Instruction> InstructionParser::nextExpressionAsEmptyInstruction() {
    size_t initialPosition = context.position();

    nextExpression();

    if (context.done()) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected a semicolon after expression, found EOF.");
    }
    if (context() != SEMICOLON_TOKEN) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected a semicolon after expression, found \"" + context().getValue() + "\".");
    }
    ++context;

    return std::unique_ptr<Instruction>(new EmptyInstruction());
}

std::unique_ptr<Instruction> InstructionParser::nextDefinition() {
    size_t initialPosition = context.position();

    std::string keyword = context().getValue();
    ++context;

    if (context.done()) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected an identifier, found EOF.");
    }
    if (context().getType() != TokenType::IDENTIFIER) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected an identifier, found \"" + context().getValue() + "\"");
    }
    std::string identifier = context().getValue();
    ++context;

    if (context.done() || context() != EQUALS_OPERATOR) {
        // It's either declaration without definition, or invalid instruction.

        std::string found;
        if (context.done()) {
            found = "EOF";
        } else {
            found = "\"" + context().getValue() + "\"";
        }

        if (keyword == "val") {
            // Definition is mandatory
            throw InstructionSyntaxError(
                context.concatenateTokensToCurrent(initialPosition),
                "Expected definition for val-decleration of \"" + identifier + "\", found " + found + ".");
        }

        if (!context.done() && context() == SEMICOLON_TOKEN) {
            // Correct val-delcaration without definition
            ++context;
            return std::unique_ptr<Instruction>(new Definition(keyword, identifier));
        }

        // Invalid definition
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected either operator \"=\" or semicolon after the definition of \"" +
                                         identifier + "\", found " + found + ".");
    }
    // Otherwise we have declaration with definition.
    ++context;

    std::unique_ptr<Expression> expression = nextExpression();

    if (context.done()) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected semicolon after the definition of \"" + identifier + "\", found EOF.");
    }
    if (context() != SEMICOLON_TOKEN) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected semicolon after the definition of \"" + identifier + "\", found \"" +
                                         context().getValue() + "\".");
    }

    return std::unique_ptr<Instruction>(new Definition(keyword, identifier, expression));
}

std::unique_ptr<Instruction> InstructionParser::nextPrinting() {
    size_t initialPosition = context.position();

    ++context;

    if (context.done()) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected opening bracket, found EOF.");
    }
    if (context() != OPENING_BRACKET_TOKEN) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected opening bracket, found \"" + context().getValue() + "\".");
    }
    ++context;

    std::unique_ptr<Expression> expression = nextExpression();

    if (context.done()) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected closing bracket, found EOF.");
    }
    if (context() != CLOSING_BRACKET_TOKEN) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected closing bracket, found \"" + context().getValue() + "\".");
    }
    ++context;

    if (context.done()) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected semicolon, found EOF.");
    }
    if (context() != SEMICOLON_TOKEN) {
        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected semicolon, found \"" + context().getValue() + "\".");
    }
    ++context;

    return std::unique_ptr<Instruction>(new Printing(expression));
}

std::unique_ptr<Instruction> InstructionParser::nextInstruction() {
    size_t initialPosition = context.position();

    if (context.done()) {
        throw InstructionSyntaxError("Expected instruction, found EOF.");
    }

    Token nextToken = context();
    TokenType type = nextToken.getType();

    if (type == TokenType::DELIMITER) {
        if (nextToken == SEMICOLON_TOKEN) {
            // An empty instruction.
            ++context;
            return std::unique_ptr<Instruction>(new EmptyInstruction());
        }

        if (nextToken == OPENING_BRACKET_TOKEN) {
            // An unused expression
            return nextExpressionAsEmptyInstruction();
        }

        throw InstructionSyntaxError("Expected an instruction, found a delimiter \"" + nextToken.getValue() + "\".");
    }

    if (type == TokenType::OPERATOR) {
        throw InstructionSyntaxError("Expected an instruction, found an operator \"" + nextToken.getValue() + "\".");
    }

    if (type == TokenType::KEYWORD) {
        if (nextToken == VAL_KEYWORD_TOKEN || nextToken == VAR_KEYWORD_TOKEN) {
            // Definition
            return nextDefinition();
        }

        if (nextToken == PRINT_KEYWORD_TOKEN) {
            // Printing
            return nextPrinting();
        }

        if (nextToken == INPUT_KEYWORD_TOKEN) {
            // An unused expression
            return nextExpressionAsEmptyInstruction();
        }

        // Currently it is impossible to reach this
        throw InstructionSyntaxError("Expected an instruction, found keyword \"" + nextToken.getValue() + "\"");
    }

    if (type == TokenType::IDENTIFIER) {
        // Either an unsued expression or an assignment
        ++context;

        if (context.done()) {
            throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                         "Expected an operator \"=\" or semicolon, found EOF.");
        }

        if (context() == SEMICOLON_TOKEN) {
            // An unused expression
            ++context;
            return std::unique_ptr<Instruction>(new EmptyInstruction());
        }

        if (context() == EQUALS_OPERATOR) {
            // Assignment
            ++context;

            std::unique_ptr<Expression> expression = nextExpression();

            if (context.done()) {
                throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                             "Expected semicolon after assignment, found EOF.");
            }
            if (context() != SEMICOLON_TOKEN) {
                throw InstructionSyntaxError(
                    context.concatenateTokensToCurrent(initialPosition),
                    "Expected semicolon after assignment, found \"" + context().getValue() + "\"");
            }
            ++context;

            return std::unique_ptr<Instruction>(new Assignment(nextToken.getValue(), expression));
        }

        throw InstructionSyntaxError(context.concatenateTokensToCurrent(initialPosition),
                                     "Expected an operator \"=\", found \"" + context().getValue() + "\".");
    }

    // In all other cases it can only be an unused expression
    return nextExpressionAsEmptyInstruction();
}

}  // namespace ast
}  // namespace cpmc
