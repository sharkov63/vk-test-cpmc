#define BOOST_TEST_MODULE ProgramParser_Test
#include "ast/ProgramParser.hpp"

#include <boost/test/included/unit_test.hpp>

#include "Exception.hpp"
#include "ast/InstructionComparator.hpp"

namespace cpmc {
namespace ast {

bool programEquals(const Program& program1, const Program& program2) {
    auto& instructions1 = program1.getInstructions();
    auto& instructions2 = program2.getInstructions();
    if (instructions1.size() != instructions2.size()) return false;
    for (size_t i = 0; i < instructions1.size(); ++i) {
        InstructionComparator comparator(*instructions1[i], *instructions2[i]);
        if (!comparator.compare()) {
            return false;
        }
    }
    return true;
}

void singleTest(const std::vector<Token>& tokens, const Program& expected) {
    ParsingContext context(tokens);
    ProgramParser parser(context);
    Program found;
    try {
        found = parser.parse();
    } catch (const SyntaxError& e) {
        BOOST_FAIL("Unexpected SyntaxError:\n" + e.getMessage());
    }
    BOOST_TEST(programEquals(expected, found));
}

BOOST_AUTO_TEST_CASE(VK_TEST_1) {
    std::vector<Token> tokens = {
        VAR_KEYWORD_TOKEN,  //
        {TokenType::IDENTIFIER, "str"},
        EQUALS_OPERATOR_TOKEN,
        {TokenType::STRING_LITERAL, "\"Hello\""},
        {TokenType::DELIMITER, ";"},
        {TokenType::IDENTIFIER, "str"},
        EQUALS_OPERATOR_TOKEN,
        {TokenType::IDENTIFIER, "str"},
        {TokenType::OPERATOR, "+"},
        {TokenType::STRING_LITERAL, "\"!\""},
        {TokenType::DELIMITER, ";"},
        PRINT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::IDENTIFIER, "str"},
        CLOSING_BRACKET_TOKEN,
    };
    std::unique_ptr<Expression> str(new IdentifierExpression("str"));
    std::unique_ptr<Expression> hello(new StringLiteralExpression("\"Hello\""));
    std::unique_ptr<Expression> exclMark(new StringLiteralExpression("\"!\""));
    std::unique_ptr<Expression> i2Rhs(new OperationExpression("+", str, exclMark));

    std::unique_ptr<Instruction> i1(new Definition("var", "str", hello));
    std::unique_ptr<Instruction> i2(new Assignment("str", i2Rhs));
    std::unique_ptr<Instruction> i3(new Printing(str));

    std::vector<std::unique_ptr<Instruction>> instructions;
    instructions.push_back(std::move(i1));
    instructions.push_back(std::move(i2));
    instructions.push_back(std::move(i3));

    Program program(std::move(instructions));

    singleTest(tokens, program);
}

BOOST_AUTO_TEST_CASE(VK_TEST_2) {
    std::vector<Token> tokens = {
        {TokenType::IDENTIFIER, "str"},
        EQUALS_OPERATOR_TOKEN,
        {TokenType::INT_LITERAL, "21"},
        {TokenType::OPERATOR, "+"},
        {TokenType::INT_LITERAL, "2"},
        {TokenType::OPERATOR, "+"},
        {TokenType::INT_LITERAL, "18"},
        SEMICOLON_TOKEN,
        PRINT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::IDENTIFIER, "str"},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
    };
    std::unique_ptr<Expression> str(new IdentifierExpression("str"));
    std::unique_ptr<Expression> i21(new IntLiteralExpression("21"));
    std::unique_ptr<Expression> i2(new IntLiteralExpression("2"));
    std::unique_ptr<Expression> i18(new IntLiteralExpression("18"));
    std::unique_ptr<Expression> i2i18(new OperationExpression("+", i2, i18));
    std::unique_ptr<Expression> sum(new OperationExpression("+", i21, i2i18));

    std::unique_ptr<Instruction> assignment(new Assignment("str", sum));

    std::vector<std::unique_ptr<Instruction>> instructions;
    instructions.push_back(std::move(assignment));

    Program program(std::move(instructions));

    singleTest(tokens, program);
}

BOOST_AUTO_TEST_CASE(VK_TEST_3) {
    std::vector<Token> tokens = {
        VAL_KEYWORD_TOKEN,  //
        {TokenType::IDENTIFIER, "worldString"},
        EQUALS_OPERATOR_TOKEN,
        {TokenType::STRING_LITERAL, "\"World\""},
        SEMICOLON_TOKEN,
        VAL_KEYWORD_TOKEN,
        {TokenType::IDENTIFIER, "answerNumber"},
        EQUALS_OPERATOR_TOKEN,
        {TokenType::INT_LITERAL, "42"},
        SEMICOLON_TOKEN,
    };
    std::unique_ptr<Expression> worldString(new IdentifierExpression("worldString"));
    std::unique_ptr<Expression> world(new StringLiteralExpression("\"World\""));
    std::unique_ptr<Expression> answerNumber(new IdentifierExpression("answerNumber"));
    std::unique_ptr<Expression> i42(new IntLiteralExpression("42"));

    std::unique_ptr<Instruction> def1(new Definition("val", "worldString", world));
    std::unique_ptr<Instruction> def2(new Definition("val", "answerNumber", i42));

    std::vector<std::unique_ptr<Instruction>> instructions;
    instructions.push_back(std::move(def1));
    instructions.push_back(std::move(def2));

    Program program(std::move(instructions));

    singleTest(tokens, program);
}

BOOST_AUTO_TEST_CASE(VK_TEST_4) {
    std::vector<Token> tokens = {
        PRINT_KEYWORD_TOKEN,  //
        OPENING_BRACKET_TOKEN,
        {TokenType::IDENTIFIER, "worldString"},
        {TokenType::OPERATOR, "+"},
        {TokenType::IDENTIFIER, "answerNumber"},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
        PRINT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::IDENTIFIER, "worldString"},
        {TokenType::OPERATOR, "-"},
        {TokenType::IDENTIFIER, "answerNumber"},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
        VAL_KEYWORD_TOKEN,
        {TokenType::IDENTIFIER, "pi"},
        EQUALS_OPERATOR_TOKEN,
        {TokenType::FLOAT_LITERAL, "3.14"},
        SEMICOLON_TOKEN,
        PRINT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::IDENTIFIER, "pi"},
        {TokenType::OPERATOR, "+"},
        {TokenType::IDENTIFIER, "answerNumber"},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
    };

    std::unique_ptr<Expression> worldString(new IdentifierExpression("worldString"));
    std::unique_ptr<Expression> answerNumber(new IdentifierExpression("answerNumber"));
    std::unique_ptr<Expression> sum(new OperationExpression("+", worldString, answerNumber));
    std::unique_ptr<Expression> dif(new OperationExpression("-", worldString, answerNumber));
    std::unique_ptr<Expression> pi(new IdentifierExpression("pi"));
    std::unique_ptr<Expression> piValue(new FloatLiteralExpression("3.14"));
    ;
    std::unique_ptr<Expression> piPlusAnswerNumber(new OperationExpression("+", pi, answerNumber));

    std::unique_ptr<Instruction> i1(new Printing(sum));
    std::unique_ptr<Instruction> i2(new Printing(dif));
    std::unique_ptr<Instruction> i3(new Definition("val", "pi", piValue));
    std::unique_ptr<Instruction> i4(new Printing(piPlusAnswerNumber));

    std::vector<std::unique_ptr<Instruction>> instructions;
    instructions.push_back(std::move(i1));
    instructions.push_back(std::move(i2));
    instructions.push_back(std::move(i3));
    instructions.push_back(std::move(i4));

    Program program(std::move(instructions));

    singleTest(tokens, program);
}

BOOST_AUTO_TEST_CASE(VK_TEST_5) {
    std::vector<Token> tokens = {
        VAL_KEYWORD_TOKEN,
        {TokenType::IDENTIFIER, "numberString"},
        EQUALS_OPERATOR_TOKEN,
        {TokenType::STRING_LITERAL, "\"134\""},
        SEMICOLON_TOKEN,
        PRINT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::IDENTIFIER, "numberString"},
        {TokenType::OPERATOR, "-"},
        {TokenType::IDENTIFIER, "answerNumber"},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
        PRINT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::IDENTIFIER, "numberString"},
        {TokenType::OPERATOR, "+"},
        {TokenType::IDENTIFIER, "answerNumber"},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
    };
    std::unique_ptr<Expression> numberString(new IdentifierExpression("numberString"));
    std::unique_ptr<Expression> s134(new StringLiteralExpression("\"134\""));
    std::unique_ptr<Expression> answerNumber(new IdentifierExpression("answerNumber"));
    std::unique_ptr<Expression> dif(new OperationExpression("-", numberString, answerNumber));
    std::unique_ptr<Expression> sum(new OperationExpression("+", numberString, answerNumber));

    std::unique_ptr<Instruction> i1(new Definition("val", "numberString", s134));
    std::unique_ptr<Instruction> i2(new Printing(dif));
    std::unique_ptr<Instruction> i3(new Printing(sum));

    std::vector<std::unique_ptr<Instruction>> instructions;
    instructions.push_back(std::move(i1));
    instructions.push_back(std::move(i2));
    instructions.push_back(std::move(i3));

    Program program(std::move(instructions));

    singleTest(tokens, program);
}

BOOST_AUTO_TEST_CASE(VK_TEST_6) {
    std::vector<Token> tokens = {
        VAL_KEYWORD_TOKEN,
        {TokenType::IDENTIFIER, "name"},
        EQUALS_OPERATOR_TOKEN,
        INPUT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::STRING_LITERAL, "\"Name: \""},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
        PRINT_KEYWORD_TOKEN,
        OPENING_BRACKET_TOKEN,
        {TokenType::STRING_LITERAL, "\"Your name is \""},
        {TokenType::OPERATOR, "+"},
        {TokenType::IDENTIFIER, "name"},
        CLOSING_BRACKET_TOKEN,
        SEMICOLON_TOKEN,
    };

    std::unique_ptr<Expression> name(new IdentifierExpression("name"));
    std::unique_ptr<Expression> nameLabel(new StringLiteralExpression("\"Name: \""));
    std::unique_ptr<Expression> input(new InputExpression(nameLabel));
    std::unique_ptr<Expression> yourNameIs(new StringLiteralExpression("\"Your name is \""));
    std::unique_ptr<Expression> printArg(new OperationExpression("+", yourNameIs, name));

    std::unique_ptr<Instruction> i1(new Definition("val", "name", input));
    std::unique_ptr<Instruction> i2(new Printing(printArg));

    std::vector<std::unique_ptr<Instruction>> instructions;
    instructions.push_back(std::move(i1));
    instructions.push_back(std::move(i2));

    Program program(std::move(instructions));

    singleTest(tokens, program);
}

}  // namespace ast
}  // namespace cpmc
