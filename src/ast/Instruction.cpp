#include "ast/Instruction.hpp"

namespace cpmc {
    namespace ast {

        /* Instruction */

        Instruction::Instruction(const InstructionType& type):
            type(type) {}

        Instruction::~Instruction() = default;


        /* EmptyInstruction */

        EmptyInstruction::EmptyInstruction():
            Instruction(InstructionType::EMPTY_INSTRUCTION) {}

        EmptyInstruction::~EmptyInstruction() = default;


        /* Definition */

        Definition::Definition(const std::string& keyword,
                               const std::string& identifier):
            Instruction(InstructionType::DEFINITION),
            keyword(keyword),
            identifier(identifier),
            expression(std::unique_ptr<Expression>(nullptr)) {}

        Definition::Definition(const std::string& keyword,
                               const std::string& identifier,
                               std::unique_ptr<Expression>& expression):
            Instruction(InstructionType::DEFINITION),
            keyword(keyword),
            identifier(identifier),
            expression(std::move(expression)) {}

        Definition::~Definition() = default;


        /* Assignment */

        Assignment::Assignment(const std::string& identifier,
                               std::unique_ptr<Expression>& expression):
            Instruction(InstructionType::ASSIGNMENT),
            identifier(identifier),
            expression(std::move(expression)) {}

        Assignment::~Assignment() = default;


        /* Printing */

        Printing::Printing(std::unique_ptr<Expression>& expression):
            Instruction(InstructionType::PRINTING),
            expression(std::move(expression)) {}

        Printing::~Printing() = default;
    }
}
