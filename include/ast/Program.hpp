#ifndef CPMC_AST_PROGRAM_HPP_INCLUDED
#define CPMC_AST_PROGRAM_HPP_INCLUDED

#include <memory>
#include <vector>

#include "ast/Instruction.hpp"

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
    Program() = default;
    Program(std::vector<std::unique_ptr<Instruction>>&& instructions);

    // field getter
    const std::vector<std::unique_ptr<Instruction>>& getInstructions() const;
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_PROGRAM_HPP_INCLUDED include guard
