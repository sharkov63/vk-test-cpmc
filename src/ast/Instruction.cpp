#include "ast/Instruction.hpp"

namespace cpmc {
    namespace ast {

        /* Instruction */

        Instruction::Instruction() {}

        Instruction::~Instruction() = default;


        /* EmptyInstruction */

        EmptyInstruction::EmptyInstruction():
            Instruction() {}

        EmptyInstruction::~EmptyInstruction() = default;

        void EmptyInstruction::accept(InstructionVisitor& visitor) const {
            visitor.visit(*this);
        }


        /* Definition */

        Definition::Definition(const std::string& keyword,
                               const std::string& identifier):
            Instruction(),
            keyword(keyword),
            identifier(identifier),
            expression(std::unique_ptr<Expression>(nullptr)) {}

        Definition::Definition(const std::string& keyword,
                               const std::string& identifier,
                               std::unique_ptr<Expression>& expression):
            Instruction(),
            keyword(keyword),
            identifier(identifier),
            expression(std::move(expression)) {}

        Definition::~Definition() = default;

        void Definition::accept(InstructionVisitor& visitor) const {
            visitor.visit(*this);
        }



        /* Assignment */

        Assignment::Assignment(const std::string& identifier,
                               std::unique_ptr<Expression>& expression):
            Instruction(),
            identifier(identifier),
            expression(std::move(expression)) {}

        Assignment::~Assignment() = default;

        void Assignment::accept(InstructionVisitor& visitor) const {
            visitor.visit(*this);
        }


        /* Printing */

        Printing::Printing(std::unique_ptr<Expression>& expression):
            Instruction(),
            expression(std::move(expression)) {}

        Printing::~Printing() = default;

        void Printing::accept(InstructionVisitor& visitor) const {
            visitor.visit(*this);
        }


        /* InstructionVisitor */

        InstructionVisitor::InstructionVisitor() = default;
        InstructionVisitor::~InstructionVisitor() = default;
    }
}
