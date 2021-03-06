#ifndef CPMC_TOKEN_HPP_INCLUDED
#define CPMC_TOKEN_HPP_INCLUDED

#include <iostream>
#include <string>

namespace cpmc {

/**
 * Types of Token.
 */
enum TokenType {
    BLANK,           /// A sequence of blank characters (all characters satisfying
                     /// std::isspace). Usually ignored
    COMMENT,         /// A comment (currently only C-style single line comment starting
                     /// with "//") Usually ignored
    DELIMITER,       /// Currently, one of '(', ')', ';'
    OPERATOR,        /// Currently, one of '+', '-', '='
    KEYWORD,         /// Currently, one of "val", "var", "input", "print"
    STRING_LITERAL,  /// A sequence of symbols not equal to " and to \n which is
                     /// surrounded by " (escaping is not supported).
    INT_LITERAL,     /// A non-empty sequence of digits.
    FLOAT_LITERAL,   /// A (possibly empty) sequence of digits, then a ., then a
                     /// non-empty sequence of digits.
    IDENTIFIER,      /// Programmer's name for a variable. A sequence of
                     /// alphanumeric characters (and underscore _), which does not
                     /// start with a digit.
};

/**
 * An atomic sequence of characters in cpm source code,
 * which has a concrete meaning.
 */
class Token {
   private:
    TokenType type;     /// The type of token.
    std::string value;  /// The value of token (it's actual string representation).

   public:
    Token();
    Token(const TokenType& type, const std::string& value);

    const TokenType& getType() const;
    const std::string& getValue() const;

    bool operator==(const Token& other) const;
    bool operator!=(const Token& other) const;

    // for debugging
    friend std::ostream& operator<<(std::ostream& stream, const Token& token);
};

const Token OPENING_BRACKET_TOKEN(TokenType::DELIMITER, "(");
const Token CLOSING_BRACKET_TOKEN(TokenType::DELIMITER, ")");
const Token SEMICOLON_TOKEN(TokenType::DELIMITER, ";");
const Token EQUALS_OPERATOR_TOKEN(TokenType::OPERATOR, "=");
const Token INPUT_KEYWORD_TOKEN(TokenType::KEYWORD, "input");
const Token PRINT_KEYWORD_TOKEN(TokenType::KEYWORD, "print");
const Token VAL_KEYWORD_TOKEN(TokenType::KEYWORD, "val");
const Token VAR_KEYWORD_TOKEN(TokenType::KEYWORD, "var");

}  // namespace cpmc

#endif  // CPMC_TOKEN_HPP_INCLUDED include guard
