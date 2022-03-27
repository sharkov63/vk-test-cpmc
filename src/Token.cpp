#include "Token.hpp"

namespace cpmc {
    Token::Token() = default;

    Token::Token(const TokenType& type, const std::string& value):
        type(type),
        value(value) {}

    const TokenType& Token::getType() const {
        return type;
    }

    const std::string& Token::getValue() const {
        return value;
    }

    bool Token::operator==(const Token& other) const {
        return type == other.type && value == other.value;
    }

    bool Token::operator!=(const Token& other) const {
        return type != other.type || value != other.value;
    }

    std::ostream& operator<<(std::ostream& stream, const Token& token) {
        return stream << "[" << token.type << " \"" << token.value << "\"]";
    }
}
