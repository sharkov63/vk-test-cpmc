#include "ast/ParsingContext.hpp"

namespace cpmc {
    namespace ast {

        ParsingContext::ParsingContext(const std::vector<Token>& tokens):
            tokens(tokens), n(tokens.size()), pos(0) {}

        bool ParsingContext::done() const {
            return pos >= n;
        }

        const Token& ParsingContext::operator[](size_t index) const {
            assert(index < n);
            return tokens[index];
        }

        const Token& ParsingContext::operator()() const {
            return tokens[pos];
        }

        size_t ParsingContext::position() const {
            return pos;
        }

        size_t ParsingContext::size() const {
            return n;
        }

        void ParsingContext::operator++() {
            ++pos;
            assert(pos <= n);
        }

        void ParsingContext::operator++(int) {
            ++pos;
            assert(pos <= n);
        }

        void ParsingContext::operator+=(size_t delta) {
            pos += delta;
            assert(pos <= n);
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

        std::string ParsingContext::concatenateTokensToCurrent(size_t l) const {
            assert(l <= pos);
            return concatenateTokens(l, pos);
        }
    }
}
