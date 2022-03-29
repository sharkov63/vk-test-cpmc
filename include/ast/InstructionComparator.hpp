#ifndef CPMC_AST_INSTRUCTION_COMPARATOR_HPP_INCLUDED
#define CPMC_AST_INSTRUCTION_COMPARATOR_HPP_INCLUDED

#include "ast/Instruction.hpp"

namespace cpmc {
namespace ast {

/**
 * A class which can compare two Instructions,
 * and output if they are equal or not.
 *
 * Useful for unit-testing.
 */
class InstructionComparator : public InstructionVisitor {
   private:
    /**
     * Instructions to compare.
     */
    const Instruction& instruction1;
    const Instruction& instruction2;

    /**
     * Result of the comparison.
     */
    bool result;

    class EmptyInstructionComparator : public InstructionVisitor {
       private:
        const EmptyInstruction& emptyInstruction;

        bool result;

       public:
        EmptyInstructionComparator(const EmptyInstruction& emptyInstruction);
        virtual ~EmptyInstructionComparator() override;

        virtual void visit(const EmptyInstruction& emptyInstruction) override final;
        virtual void visit(const Definition& definition) override final;
        virtual void visit(const Assignment& assignment) override final;
        virtual void visit(const Printing& printingInstruction) override final;

        bool compare();
    };

    class DefinitionComparator : public InstructionVisitor {
       private:
        const Definition& definition;

        bool result;

       public:
        DefinitionComparator(const Definition& definition);
        virtual ~DefinitionComparator() override;

        virtual void visit(const EmptyInstruction& emptyInstruction) override final;
        virtual void visit(const Definition& definition) override final;
        virtual void visit(const Assignment& assignment) override final;
        virtual void visit(const Printing& printingInstruction) override final;

        bool compare();
    };

    class AssignmentComparator : public InstructionVisitor {
       private:
        const Assignment& assignment;

        bool result;

       public:
        AssignmentComparator(const Assignment& assignment);
        virtual ~AssignmentComparator() override;

        virtual void visit(const EmptyInstruction& emptyInstruction) override final;
        virtual void visit(const Definition& definition) override final;
        virtual void visit(const Assignment& assignment) override final;
        virtual void visit(const Printing& printingInstruction) override final;

        bool compare();
    };

    class PrintingComparator : public InstructionVisitor {
       private:
        const Printing& printing;

        bool result;

       public:
        PrintingComparator(const Printing& printing);
        virtual ~PrintingComparator() override;

        virtual void visit(const EmptyInstruction& emptyInstruction) override final;
        virtual void visit(const Definition& definition) override final;
        virtual void visit(const Assignment& assignment) override final;
        virtual void visit(const Printing& printingInstruction) override final;

        bool compare();
    };

   public:
    InstructionComparator(const Instruction& instruction1, const Instruction& instruction2);
    virtual ~InstructionComparator() override;

    virtual void visit(const EmptyInstruction& emptyInstruction) override final;
    virtual void visit(const Definition& definition) override final;
    virtual void visit(const Assignment& assignment) override final;
    virtual void visit(const Printing& printingInstruction) override final;

    /**
     * Compares the instructions.
     *
     * @return true if the instructions are equal.
     */
    bool compare();
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_INSTRUCTION_COMPARATOR_HPP_INCLUDED include guard
