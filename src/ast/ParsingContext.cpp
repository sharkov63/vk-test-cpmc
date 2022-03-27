#include "ast/ParsingContext.hpp"

namespace cpmc {
    namespace ast {

        ParsingContext::ParsingContext(const std::vector<Token>& tokens):
            tokens(tokens), n(tokens.size()), pos(0) {}

        bool ParsingContext::done() const {
            return pos >= n;
        }

        /**
         * Returns the token at given position.
         */
        const Token& ParsingContext::operator[](size_t index) const {
            assert(index < n);
            return tokens[index];
        }

        /**
         * Returns the token under current parsing position.
         */
        const Token& ParsingContext::operator()() const {
            return tokens[pos];
        }

        /**
         * Returns current parsing position.
         */
        size_t ParsingContext::position() const {
            return pos;
        }

        /**
         * Increments parsing position.
         */
        void ParsingContext::operator++() {
            ++pos;
        }

        /**
         * Increments parsing position.
         */
        void ParsingContext::operator++(int) {
            ++pos;
        }

        std::string ParsingContext::concatenateTokens(size_t l, size_t r) const {
            assert(l <= r);
            assert(r < n);
            std::string result = "";
            for (size_t i = l; i <= r; ++i) {
                result += tokens[i].getValue();
            }
            return result;
        }
    }
}
