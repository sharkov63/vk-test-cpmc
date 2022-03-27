#ifndef CPMC_AST_PARSING_CONTEXT_HPP_INCLUDED
#define CPMC_AST_PARSING_CONTEXT_HPP_INCLUDED

#include "Token.hpp"

#include <vector>
#include <cassert>

namespace cpmc {
    namespace ast {

        /**
         * A helper class, which stores tokenized source code,
         * and the current position.
         *
         * The idea is that there are many objects who can
         * take part in parsing procedure, but they all have
         * the same context, which is a list of tokens,
         * and the position of next token.
         * Thus way we don't have to copy all token list
         * for each parsing object.
         */
        class ParsingContext {
            private:
                /**
                 * Tokenized source code.
                 */
                const std::vector<Token> tokens;

                /**
                 * The number of tokens.
                 */
                const size_t n;

                /**
                 * Current position in parsing procedure.
                 */
                size_t pos;

            public:
                explicit ParsingContext(const std::vector<Token>& tokens);

                /**
                 * Returns the token at given position.
                 */
                const Token& operator[](size_t index) const;

                /**
                 * Returns the token under current parsing position.
                 */
                const Token& operator()() const;

                /**
                 * Returns current parsing position.
                 */
                size_t position() const;

                /**
                 * Increments parsing position.
                 */
                void operator++();

                /**
                 * Increments parsing position.
                 */
                void operator++(int);
        };
    }
}

#endif  // CPMC_AST_PARSING_CONTEXT_HPP_INCLUDED include guard
