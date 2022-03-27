#define BOOST_TEST_MODULE ExpressionParser_Test
#include <boost/test/included/unit_test.hpp>

#include "Token.hpp"
#include "Exception.hpp"
#include "ast/Expression.hpp"
#include "ast/ExpressionParser.hpp"

#include <vector>

BOOST_TEST_DONT_PRINT_LOG_VALUE( cpmc::ast::Expression );

namespace cpmc {
    namespace ast {

        void singleTest(const std::vector<Token>& tokens,
                        const Expression& expected) {
            ParsingContext context(tokens);
            ExpressionParser parser(context);
            std::unique_ptr<Expression> found = parser.nextExpression();
            BOOST_TEST(*found == expected);
        }

        void throwTest(std::vector<Token> tokens) {
            ParsingContext context(tokens);
            ExpressionParser parser(context);
            BOOST_CHECK_THROW(parser.nextExpression(), ExpressionSyntaxError);
        }

        BOOST_AUTO_TEST_CASE( TEST_STRING_LITERAL ) {
            std::vector<Token> tokens = {
                {TokenType::STRING_LITERAL, "\"Hello\""},
            };
            StringLiteralExpression expected("\"Hello\"");
            singleTest(tokens, expected);
        }

        BOOST_AUTO_TEST_CASE( TEST_IDENTIFIER ) {
            std::vector<Token> tokens = {
                {TokenType::IDENTIFIER, "str"},
            };
            IdentifierExpression expected("str");
            singleTest(tokens, expected);
        }

        BOOST_AUTO_TEST_CASE( TEST_IDENTIFIER_PLUS_LITERAL ) {
            std::vector<Token> tokens = {
                {TokenType::IDENTIFIER, "str"},
                {TokenType::OPERATOR, "+"},
                {TokenType::STRING_LITERAL, "\"!\""},
            };
            std::unique_ptr<Expression> v1(new IdentifierExpression("str"));
            std::unique_ptr<Expression> v2(new StringLiteralExpression("\"!\""));
            OperationExpression v3("+", v1, v2);
            singleTest(tokens, v3);
        }

        BOOST_AUTO_TEST_CASE( TEST_SUM_OF_THREE_INTS ) {
            std::vector<Token> tokens = {
                {TokenType::INT_LITERAL, "21"},
                {TokenType::OPERATOR, "+"},
                {TokenType::INT_LITERAL, "2"},
                {TokenType::OPERATOR, "+"},
                {TokenType::INT_LITERAL, "18"},
                {TokenType::DELIMITER, ";"},
            };
            std::unique_ptr<Expression> v1(new IntLiteralExpression("21"));
            std::unique_ptr<Expression> v2(new IntLiteralExpression("2"));
            std::unique_ptr<Expression> v3(new IntLiteralExpression("18"));
            std::unique_ptr<Expression> u1(new OperationExpression("+", v1, v2));
            std::unique_ptr<Expression> u2(new OperationExpression("+", u1, v3));
            singleTest(tokens, *u2);
        }

        BOOST_AUTO_TEST_CASE( SUM_OF_TWO_IDENTIFIERS ) {
            std::vector<Token> tokens = {
                {TokenType::IDENTIFIER, "worldString"},
                {TokenType::OPERATOR, "-"},
                {TokenType::IDENTIFIER, "answerNumber"},
            };
            std::unique_ptr<Expression> v1(new IdentifierExpression("worldString"));
            std::unique_ptr<Expression> v2(new IdentifierExpression("answerNumber"));
            OperationExpression v3("-", v1, v2);
            singleTest(tokens, v3);
        }

        BOOST_AUTO_TEST_CASE( INPUT_OF_STRING_LITERAL ) {
            std::vector<Token> tokens = {
                {TokenType::KEYWORD, "input"},
                {TokenType::DELIMITER, "("},
                {TokenType::STRING_LITERAL, "\"Name: \""},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ";"},
                {TokenType::DELIMITER, ";"},
            };
            std::unique_ptr<Expression> v(new StringLiteralExpression("\"Name: \""));
            std::unique_ptr<Expression> u(new InputExpression(v));
            singleTest(tokens, *u);
        }

        BOOST_AUTO_TEST_CASE( REGULAR_BRACKET_SEQUENCE_1 ) {
            std::vector<Token> tokens = {
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, "("},
                {TokenType::INT_LITERAL, "1"},
                {TokenType::OPERATOR, "+"},
                {TokenType::INT_LITERAL, "2"},
                {TokenType::DELIMITER, ")"},
                {TokenType::OPERATOR, "-"},
                {TokenType::DELIMITER, "("},
                {TokenType::INT_LITERAL, "3"},
                {TokenType::OPERATOR, "-"},
                {TokenType::INT_LITERAL, "4"},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ";"},
                {TokenType::DELIMITER, ";"},
            };
            std::unique_ptr<Expression> v1(new IntLiteralExpression("1"));
            std::unique_ptr<Expression> v2(new IntLiteralExpression("2"));
            std::unique_ptr<Expression> v3(new IntLiteralExpression("3"));
            std::unique_ptr<Expression> v4(new IntLiteralExpression("4"));
            std::unique_ptr<Expression> u1(new OperationExpression("+", v1, v2));
            std::unique_ptr<Expression> u2(new OperationExpression("-", v3, v4));
            std::unique_ptr<Expression>  w(new OperationExpression("-", u1, u2));
            singleTest(tokens, *w);
        }

        BOOST_AUTO_TEST_CASE( TWO_CONCATENATED_EXPRESSIONS ) {
            std::vector<Token> tokens = {
                {TokenType::STRING_LITERAL, "\"A\""},
                {TokenType::STRING_LITERAL, "\"B\""},
            };
            StringLiteralExpression expected("\"A\"");
            singleTest(tokens, expected);
        }

        BOOST_AUTO_TEST_CASE( TWO_SEMICOLON_SEPARATED_EXPRESSIONS ) {
            std::vector<Token> tokens = {
                {TokenType::IDENTIFIER, "variable1"},
                {TokenType::DELIMITER, ";"},
                {TokenType::DELIMITER, ";"},
                {TokenType::IDENTIFIER, "variable2"},
                {TokenType::DELIMITER, ";"},
                {TokenType::DELIMITER, ";"},
                {TokenType::DELIMITER, ";"},
            };
            IdentifierExpression expected("variable1");
            singleTest(tokens, expected);
        }

        BOOST_AUTO_TEST_CASE( INPUT_WITH_NESTED_EXPRESSION ) {
            std::vector<Token> tokens = {
                {TokenType::KEYWORD, "input"},
                {TokenType::DELIMITER, "("},
                {TokenType::STRING_LITERAL, "\"The \""},
                {TokenType::OPERATOR, "+"},
                {TokenType::INT_LITERAL, "3"},
                {TokenType::OPERATOR, "+"},
                {TokenType::STRING_LITERAL, "\"Bells\""},
                {TokenType::DELIMITER, ")"},
            };
            std::unique_ptr<Expression> v1(new StringLiteralExpression("\"The \""));
            std::unique_ptr<Expression> v2(new IntLiteralExpression("3"));
            std::unique_ptr<Expression> v3(new StringLiteralExpression("\"Bells\""));
            std::unique_ptr<Expression> u(new OperationExpression("+", v1, v2));
            std::unique_ptr<Expression> w(new OperationExpression("+", u, v3));
            std::unique_ptr<Expression> t(new InputExpression(w));
            singleTest(tokens, *t);
        }

        BOOST_AUTO_TEST_CASE( DOUBLE_INPUT ) {
            std::vector<Token> tokens = {
                {TokenType::KEYWORD, "input"},
                {TokenType::DELIMITER, "("},
                {TokenType::KEYWORD, "input"},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ")"},
            };
            std::unique_ptr<Expression> a(new InputExpression());
            std::unique_ptr<Expression> b(new InputExpression(a));
            singleTest(tokens, *b);
        }

        BOOST_AUTO_TEST_CASE( EMPTY_EXPRESSION ) {
            std::vector<Token> tokens = {};
            throwTest(tokens);
        }

        BOOST_AUTO_TEST_CASE( EMPTY_EXPRESSION_WITH_REGULAR_BRACKET_SEQ ) {
            std::vector<Token> tokens = {
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, ")"},
            };
            throwTest(tokens);
        }

        BOOST_AUTO_TEST_CASE( EMPTY_EXPRESSION_WITH_IRREGULAR_BRACKET_SEQ ) {
            std::vector<Token> tokens = {
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, ")"},
            };
            throwTest(tokens);
        }

        BOOST_AUTO_TEST_CASE( EMPTY_EXPRESSION_WITH_IRREGULAR_BRACKET_SEQ_1 ) {
            std::vector<Token> tokens = {
                {TokenType::DELIMITER, ")"},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, "("},
                {TokenType::DELIMITER, ")"},
            };
            throwTest(tokens);
        }

        BOOST_AUTO_TEST_CASE( STARTING_ON_WRONG_KEYWORD ) {
            std::vector<Token> tokens = {
                {TokenType::KEYWORD, "val"},
                {TokenType::IDENTIFIER, "foo"},
                {TokenType::OPERATOR, "="},
                {TokenType::INT_LITERAL, "2"},
                {TokenType::DELIMITER, ";"},
            };
            throwTest(tokens);
        }

        BOOST_AUTO_TEST_CASE( STARTING_ON_SEMICOLON ) {
            std::vector<Token> tokens = {
                {TokenType::DELIMITER, ";"},
                {TokenType::INT_LITERAL, "12"},
                {TokenType::OPERATOR, "+"},
                {TokenType::INT_LITERAL, "3"},
                {TokenType::OPERATOR, "+"},
                {TokenType::STRING_LITERAL, "\"That's Amore\""},
            };
            throwTest(tokens);
        }

        BOOST_AUTO_TEST_CASE( STARTING_ON_OPERATOR ) {
            std::vector<Token> tokens = {
                {TokenType::OPERATOR, "+"},
                {TokenType::STRING_LITERAL, "\"Like a big pizza pie\""},
                {TokenType::OPERATOR, "+"},
                {TokenType::STRING_LITERAL, "\"Too much wine\""},
            };
            throwTest(tokens);
        }
    }
}
