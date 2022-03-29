#ifndef CPMC_AST_INSTRUCTION_DEBUG_PRINTER_HPP_INCLUDED
#define CPMC_AST_INSTRUCTION_DEBUG_PRINTER_HPP_INCLUDED

#include "ast/Instruction.hpp"

namespace cpmc {
namespace ast {

/**
 * Prints an Instruction to given std::ostream.
 */
class InstructionDebugPrinter : public InstructionVisitor {
   private:
    std::ostream& stream;

   public:
    InstructionDebugPrinter() = delete;
    InstructionDebugPrinter(std::ostream& stream);
    virtual ~InstructionDebugPrinter() override;

    virtual void visit(const EmptyInstruction& emptyInstruction) override final;
    virtual void visit(const Definition& definition) override final;
    virtual void visit(const Assignment& assignment) override final;
    virtual void visit(const Printing& printingInstruction) override final;
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_INSTRUCTION_DEBUG_PRINTER_HPP_INCLUDED include guard
