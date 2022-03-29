#ifndef CPMC_TOKENIZER_HPP_INCLUDED
#define CPMC_TOKENIZER_HPP_INCLUDED

#include <set>
#include <vector>

#include "Token.hpp"

namespace cpmc {

/**
 * Splits cpm source code into a sequence of tokens.
 */
class Tokenizer {
   public:
    /// Some symbols with special meaning.
    static const char COMMENT_SYMBOL = '/';
    static const char STRING_LITERAL_LEFT_DELIMITER = '\"';
    static const char STRING_LITERAL_RIGHT_DELIMITER = '\"';

    /// Useful helper functions.
    static bool isDelimiter(char c);
    static bool isOperator(char c);
    static bool isDigit(char c);
    static bool isNumeric(char c);
    static bool isAlphabetic(char c);
    static bool isWordSymbol(char c);

    /// Contains all keywords in cpm language.
    static const std::set<std::string> keywords;

   private:
    const std::string& s;  /// The current string which is being tokenized.
    size_t n;              /// The length of s
    size_t i;              /// The position of next symbol to read.

    /**
     * Caller should guarantee that:
     * i < n && std::isspace(s[i])
     */
    Token nextBlankToken() noexcept;

    /**
     * Caller should guarantee that:
     * i < n && s[i] == COMMENT_SYMBOL
     *
     * @throws InvalidTokenException
     */
    Token nextCommentToken();

    /**
     * Caller should guarantee that:
     * i < n && s[i] == STRING_LITERAL_LEFT_DELIMITER
     *
     * @throws InvalidTokenException
     */
    Token nextStringLiteralToken();

    /**
     * Caller should guarantee that:
     * i < n && isNumeric(s[i])
     */
    Token nextNumericLiteralToken();

    /**
     * Caller should guarantee that:
     * i < n && isWordSymbol(s[i])
     */
    Token nextWordToken();

    /**
     * Returns next token in the string.
     *
     * Caller should check that the next token exists.
     *
     * @throws InvalidTokenException on invalid token;
     * @throws NoMoreTokensException when there is no nextToken.
     */
    Token nextToken();

   public:
    /**
     * Creates a Tokenizer for a given source code.
     *
     * @param s cpm source code to tokenize.
     */
    Tokenizer(const std::string& s);

    /**
     * Tokenizes given cpm source code.
     *
     * @return a sequence of tokens (skipping tokens with type TokenType::BLANK
     * and TokenType::COMMENT).
     * @throws InvalidTokenException on invalid token.
     */
    std::vector<Token> tokenize();
};

}  // namespace cpmc

#endif  // CPMC_TOKENIZER_HPP_INCLUDED include guard
