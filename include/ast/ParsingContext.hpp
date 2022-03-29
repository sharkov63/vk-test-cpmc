#ifndef CPMC_AST_PARSING_CONTEXT_HPP_INCLUDED
#define CPMC_AST_PARSING_CONTEXT_HPP_INCLUDED

#include <vector>

#include "Token.hpp"

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
     * Returns true iff we reached the end (pos >= n)
     */
    bool done() const;

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
     * Returns the size of the token list.
     */
    size_t size() const;

    /**
     * Increments parsing position.
     *
     * Caller must ensure the new position does not exceed n.
     */
    void operator++();

    /**
     * Increments parsing position.
     *
     * Caller must ensure the new position does not exceed n.
     */
    void operator++(int);

    /**
     * Increments parsing position on given delta.
     *
     * Caller must ensure the new position does not exceed n.
     */
    void operator+=(size_t delta);

    /**
     * Returns concatenated tokens in positions l..r (inclusive).
     * Useful for exception handling.
     */
    std::string concatenateTokens(size_t l, size_t r) const;

    /**
     * Returns concatenated tokens in positions l..pos (inclusive).
     * Useful for exception handling.
     */
    std::string concatenateTokensToCurrent(size_t l) const;
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_PARSING_CONTEXT_HPP_INCLUDED include guard
