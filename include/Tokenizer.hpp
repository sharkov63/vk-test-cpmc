#ifndef CPMC_TOKENIZER_HPP_INCLUDED
#define CPMC_TOKENIZER_HPP_INCLUDED

#include "Token.hpp"

#include <vector>

namespace cpmc {
    /**
     * Splits cpm source code into a sequence of tokens.
     */
    class Tokenizer {
        public:
            Tokenizer();

            /**
             * Tokenizes given cpm source code.
             *
             * @param source the raw cpm source code to tokenize.
             * @return a sequence of tokens (skipping tokens with type TokenType::BLANK and TokenType::COMMENT).
             * @throws InvalidTokenException on invalid token.
             */
            std::vector<Token> tokenize(const std::string& source);
    };
}

#endif  // CPMC_TOKENIZER_HPP_INCLUDED include guard
