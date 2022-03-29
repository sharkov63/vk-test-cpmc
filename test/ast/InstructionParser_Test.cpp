#define BOOST_TEST_MODULE InstructionParser_Test
#include "ast/InstructionParser.hpp"

#include <boost/test/included/unit_test.hpp>

#include "Exception.hpp"
#include "ast/InstructionComparator.hpp"
#include "ast/InstructionDebugPrinter.hpp"
#include "ast/ParsingContext.hpp"

namespace cpmc {
namespace ast {

std::ostream& operator<<(std::ostream& stream, const Instruction& instruction) {
    InstructionDebugPrinter printer(stream);
    instruction.accept(printer);
    return stream;
}

void singleTest(const std::vector<Token>& tokens, const Instruction& expected) {
    ParsingContext context(tokens);
    InstructionParser parser(context);
    std::unique_ptr<Instruction> found = parser.nextInstruction();
    InstructionComparator comparator(*found, expected);
    BOOST_TEST(comparator.compare());
}

void throwTest(std::vector<Token> tokens) {
    ParsingContext context(tokens);
    InstructionParser parser(context);
    BOOST_CHECK_THROW(parser.nextInstruction(), InstructionSyntaxError);
}

BOOST_AUTO_TEST_CASE(STR_VAR_DEFINITION) {
    std::vector<Token> tokens = {
        {TokenType::KEYWORD, "var"}, {TokenType::IDENTIFIER, "str"},
        {TokenType::OPERATOR, "="},  {TokenType::STRING_LITERAL, "\"Hello\""},
        {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e(new StringLiteralExpression("\"Hello\""));
    Definition a("var", "str", e);
    singleTest(tokens, a);
}

BOOST_AUTO_TEST_CASE(ASSIGNMENT_TO_SUM) {
    std::vector<Token> tokens = {
        {TokenType::IDENTIFIER, "str"}, {TokenType::OPERATOR, "="},           {TokenType::IDENTIFIER, "str"},
        {TokenType::OPERATOR, "+"},     {TokenType::STRING_LITERAL, "\"!\""}, {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e1(new IdentifierExpression("str"));
    std::unique_ptr<Expression> e2(new StringLiteralExpression("\"!\""));
    std::unique_ptr<Expression> e3(new OperationExpression("+", e1, e2));
    std::unique_ptr<Instruction> i1(new Assignment("str", e3));
    singleTest(tokens, *i1);
}

BOOST_AUTO_TEST_CASE(PRINT_STR) {
    std::vector<Token> tokens = {
        {TokenType::KEYWORD, "print"}, {TokenType::DELIMITER, "("}, {TokenType::IDENTIFIER, "str"},
        {TokenType::DELIMITER, ")"},   {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e(new IdentifierExpression("str"));
    std::unique_ptr<Instruction> i(new Printing(e));
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(ASSIGNMENT_TRIPLE_SUM) {
    std::vector<Token> tokens = {
        {TokenType::IDENTIFIER, "str"}, {TokenType::OPERATOR, "="},    {TokenType::INT_LITERAL, "21"},
        {TokenType::OPERATOR, "+"},     {TokenType::INT_LITERAL, "2"}, {TokenType::OPERATOR, "+"},
        {TokenType::INT_LITERAL, "18"}, {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e1(new IntLiteralExpression("21"));
    std::unique_ptr<Expression> e2(new IntLiteralExpression("2"));
    std::unique_ptr<Expression> e3(new IntLiteralExpression("18"));

    std::unique_ptr<Expression> e4(new OperationExpression("+", e2, e3));
    std::unique_ptr<Expression> e5(new OperationExpression("+", e1, e4));

    std::unique_ptr<Instruction> i(new Assignment("str", e5));
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(VAL_INT_DEFINITION) {
    std::vector<Token> tokens = {
        {TokenType::KEYWORD, "val"}, {TokenType::IDENTIFIER, "answerNumber"},
        {TokenType::OPERATOR, "="},  {TokenType::INT_LITERAL, "42"},
        {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e(new IntLiteralExpression("42"));
    std::unique_ptr<Instruction> i(new Definition("val", "answerNumber", e));
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(PRINT_OF_SUM) {
    std::vector<Token> tokens = {
        {TokenType::KEYWORD, "print"},
        {TokenType::DELIMITER, "("},
        {TokenType::IDENTIFIER, "worldString"},
        {TokenType::OPERATOR, "+"},
        {TokenType::IDENTIFIER, "answerNumber"},
        {TokenType::DELIMITER, ")"},
        {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e1(new IdentifierExpression("worldString"));
    std::unique_ptr<Expression> e2(new IdentifierExpression("answerNumber"));
    std::unique_ptr<Expression> e3(new OperationExpression("+", e1, e2));

    std::unique_ptr<Instruction> i(new Printing(e3));
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(VAL_FLOAT_DEFINITION) {
    std::vector<Token> tokens = {
        {TokenType::KEYWORD, "val"},      {TokenType::IDENTIFIER, "pi"}, {TokenType::OPERATOR, "="},
        {TokenType::INT_LITERAL, "3.14"}, {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e(new FloatLiteralExpression("3.14"));
    std::unique_ptr<Instruction> i(new Definition("val", "pi", e));
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(DEFINITION_FROM_INPUT) {
    std::vector<Token> tokens = {
        {TokenType::KEYWORD, "val"},   {TokenType::IDENTIFIER, "name"}, {TokenType::OPERATOR, "="},
        {TokenType::KEYWORD, "input"}, {TokenType::DELIMITER, "("},     {TokenType::STRING_LITERAL, "\"Name: \""},
        {TokenType::DELIMITER, ")"},   {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e1(new StringLiteralExpression("\"Name: \""));
    std::unique_ptr<Expression> e2(new InputExpression(e1));
    std::unique_ptr<Instruction> i(new Definition("val", "name", e2));
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(EMPTY_INSTRUCTION) {
    std::vector<Token> tokens = {
        {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Instruction> i(new EmptyInstruction());
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(EXPRESSION_IS_EMPTY_INSTRUCTION) {
    std::vector<Token> tokens = {
        {TokenType::DELIMITER, "("}, {TokenType::DELIMITER, "("},   {TokenType::INT_LITERAL, "21"},
        {TokenType::OPERATOR, "+"},  {TokenType::INT_LITERAL, "8"}, {TokenType::DELIMITER, ")"},
        {TokenType::DELIMITER, ")"}, {TokenType::DELIMITER, ";"},   {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Instruction> i(new EmptyInstruction());
    singleTest(tokens, *i);
}

BOOST_AUTO_TEST_CASE(TWO_CONCATENATED_INSTRUCTIONS) {
    std::vector<Token> tokens = {
        {TokenType::KEYWORD, "print"},       {TokenType::DELIMITER, "("}, {TokenType::FLOAT_LITERAL, "5.5"},
        {TokenType::DELIMITER, ")"},         {TokenType::DELIMITER, ";"}, {TokenType::KEYWORD, "val"},
        {TokenType::IDENTIFIER, "variable"}, {TokenType::DELIMITER, "="}, {TokenType::STRING_LITERAL, "\"oops\""},
        {TokenType::DELIMITER, ";"},
    };
    std::unique_ptr<Expression> e(new FloatLiteralExpression("5.5"));
    std::unique_ptr<Instruction> i(new Printing(e));
    singleTest(tokens, *i);
}

// throw tests

BOOST_AUTO_TEST_CASE(TOTALLY_EMPTY_EXPRESSION) {
    std::vector<Token> tokens = {};
    throwTest(tokens);
}

BOOST_AUTO_TEST_CASE(NO_FINISHING_SEMICOLON) {
    std::vector<Token> tokens = {
        {TokenType::IDENTIFIER, "g"},
        {TokenType::OPERATOR, "="},
        {TokenType::IDENTIFIER, "f"},
    };
    throwTest(tokens);
}

BOOST_AUTO_TEST_CASE(NO_EXPECTED_EXPRESSION_IN_ASSIGNMENT) {
    std::vector<Token> tokens = {
        {TokenType::IDENTIFIER, "g"},
        {TokenType::OPERATOR, "="},
        {TokenType::DELIMITER, ";"},
    };
    throwTest(tokens);
}

BOOST_AUTO_TEST_CASE(EMPTY_EXPRESSION_REGULAR_BRACKET_SEQUENCE) {
    std::vector<Token> tokens = {
        {TokenType::DELIMITER, "("}, {TokenType::DELIMITER, "("}, {TokenType::DELIMITER, ")"},
        {TokenType::DELIMITER, ")"}, {TokenType::DELIMITER, ")"},
    };
    throwTest(tokens);
}

BOOST_AUTO_TEST_CASE(STARTING_ON_OPERATOR_PLUS) {
    std::vector<Token> tokens = {
        {TokenType::OPERATOR, "+"},
        {TokenType::STRING_LITERAL, "\"abacaba\""},
        {TokenType::DELIMITER, ";"},
    };
    throwTest(tokens);
}

BOOST_AUTO_TEST_CASE(STARTING_ON_OPERATOR_EQUALS) {
    std::vector<Token> tokens = {
        {TokenType::OPERATOR, "="},
        {TokenType::STRING_LITERAL, "\"cdef\""},
        {TokenType::DELIMITER, ";"},
    };
    throwTest(tokens);
}

}  // namespace ast
}  // namespace cpmc
