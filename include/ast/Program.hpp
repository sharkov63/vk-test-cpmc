#ifndef CPMC_AST_PROGRAM_HPP_INCLUDED
#define CPMC_AST_PROGRAM_HPP_INCLUDED

#include "ast/Instruction.hpp"

#include <vector>
#include <memory>

namespace cpmc {
    namespace ast {

        /**
         * A CPM program: a sequence of Instructions.
         */
        class Program {
            private:
                /**
                 * The sequence of Instructions.
                 */
                std::vector<std::unique_ptr<Instruction>> instructions;

            public:
                Program(const std::vector<std::unique_ptr<Instruction>>& instructions);
        };
    }
}

#endif  // CPMC_AST_PROGRAM_HPP_INCLUDED include guard
