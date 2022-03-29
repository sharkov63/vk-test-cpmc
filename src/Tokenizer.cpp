#include "Tokenizer.hpp"

#include "Exception.hpp"

namespace cpmc {

bool Tokenizer::isDelimiter(char c) { return c == '(' || c == ')' || c == ';'; }

bool Tokenizer::isOperator(char c) { return c == '+' || c == '-' || c == '='; }

bool Tokenizer::isDigit(char c) { return '0' <= c && c <= '9'; }

bool Tokenizer::isNumeric(char c) { return c == '.' || isDigit(c); }

bool Tokenizer::isAlphabetic(char c) { return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'); }

bool Tokenizer::isWordSymbol(char c) { return c == '_' || isAlphabetic(c) || isDigit(c); }

const std::set<std::string> Tokenizer::keywords = {
    "val",
    "var",
    "input",
    "print",
};

Token Tokenizer::nextBlankToken() noexcept {
    size_t i0 = i;
    ++i;
    while (i < n && std::isspace(s[i])) {
        ++i;
    }
    return Token(TokenType::BLANK, s.substr(i0, i - i0));
}

Token Tokenizer::nextCommentToken() {
    size_t i0 = i;

    // candidate for a comment
    if (i + 1 >= n || s[i + 1] != COMMENT_SYMBOL) {
        std::string cs = std::string(1, COMMENT_SYMBOL);
        throw InvalidTokenException(cs, "Expected a comment starting with \"" + cs + cs + "\".");
    }
    i += 2;

    // definitely a comment at this point
    // we should read until the \n symbol
    while (i < n && s[i] != '\n') {
        ++i;
    }

    // either we reached the end
    // or reached the new line symbol
    return Token(TokenType::COMMENT, s.substr(i0, i - i0));
}

Token Tokenizer::nextStringLiteralToken() {
    size_t i0 = i;
    ++i;
    while (i < n && s[i] != STRING_LITERAL_RIGHT_DELIMITER) {
        if (s[i] == '\n') {
            throw InvalidTokenException(s.substr(i0, i - i0),
                                        "A string literal has not been closed before line break.");
        }
        ++i;
    }
    if (i == n) {
        // haven't found STRING_LITERAL_RIGHT_DELIMITER
        throw InvalidTokenException(s.substr(i, i - i0),
                                    "A string literal has not been closed before end of file.");
    }
    ++i;  // skip STRING_LITERAL_RIGHT_DELIMITER
    return Token(TokenType::STRING_LITERAL, s.substr(i0, i - i0));
}

Token Tokenizer::nextNumericLiteralToken() {
    size_t i0 = i;
    size_t dotCount = 0;
    while (i < n && isNumeric(s[i])) {
        if (s[i] == '.') {
            ++dotCount;
        }
        ++i;
    }
    std::string token = s.substr(i0, i - i0);
    if (dotCount > 1) {
        throw InvalidTokenException(token,
                                    "A floating-point number literal contains more than one dot.");
    }
    if (s[i - 1] == '.') {
        throw InvalidTokenException(token, "A floating-point number literal ends with a dot.");
    }
    if (dotCount == 0) {
        return Token(TokenType::INT_LITERAL, token);
    }
    return Token(TokenType::FLOAT_LITERAL, token);
}

Token Tokenizer::nextWordToken() {
    size_t i0 = i;
    while (i < n && isWordSymbol(s[i])) {
        ++i;
    }
    std::string token = s.substr(i0, i - i0);
    TokenType type;
    if (keywords.find(token) != keywords.end()) {
        type = TokenType::KEYWORD;
    } else {
        type = TokenType::IDENTIFIER;
    }
    return Token(type, token);
}

Token Tokenizer::nextToken() {
    char c = s[i];
    if (isspace(c)) {
        return nextBlankToken();
    }
    if (c == COMMENT_SYMBOL) {
        return nextCommentToken();
    }
    if (isDelimiter(c)) {
        return Token(TokenType::DELIMITER, s.substr(i++, 1));
    }
    if (isOperator(c)) {
        return Token(TokenType::OPERATOR, s.substr(i++, 1));
    }
    if (c == STRING_LITERAL_LEFT_DELIMITER) {
        return nextStringLiteralToken();
    }
    if (isNumeric(c)) {
        return nextNumericLiteralToken();
    }
    if (isWordSymbol(c)) {
        return nextWordToken();
    }
    throw InvalidTokenException(s.substr(i, 1), "Illegal character is source code.");
}

Tokenizer::Tokenizer(const std::string& s) : s(s), n(s.size()), i(0) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    while (i < n) {
        Token token;
        try {
            token = nextToken();
        } catch (const NoMoreTokensException& e) {
            break;
        } catch (const InvalidTokenException& e) {
            // TODO add some coordinates in the file of invalid token
            // or maybe store coordinates of all tokens
            throw e;
        }
        if (token.getType() == TokenType::BLANK || token.getType() == TokenType::COMMENT) {
            // skip these
            continue;
        }
        tokens.push_back(token);
    }
    return tokens;
}

}  // namespace cpmc
