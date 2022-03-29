#include "ast/Instruction.hpp"

namespace cpmc {
namespace ast {

/* Instruction */

Instruction::Instruction() {}

Instruction::~Instruction() = default;

/* EmptyInstruction */

EmptyInstruction::EmptyInstruction() : Instruction() {}

EmptyInstruction::~EmptyInstruction() = default;

void EmptyInstruction::accept(InstructionVisitor& visitor) const { visitor.visit(*this); }

/* Definition */

Definition::Definition(const std::string& keyword, const std::string& identifier)
    : Instruction(),
      keyword(keyword),
      identifier(identifier),
      expression(std::unique_ptr<Expression>(nullptr)) {}

Definition::Definition(const std::string& keyword, const std::string& identifier,
                       std::unique_ptr<Expression>& expression)
    : Instruction(), keyword(keyword), identifier(identifier), expression(std::move(expression)) {}

Definition::~Definition() = default;

const std::string& Definition::getKeyword() const { return keyword; }

const std::string& Definition::getIdentifier() const { return identifier; }

const std::unique_ptr<Expression>& Definition::getExpressionPtr() const { return expression; }

void Definition::accept(InstructionVisitor& visitor) const { visitor.visit(*this); }

/* Assignment */

Assignment::Assignment(const std::string& identifier, std::unique_ptr<Expression>& expression)
    : Instruction(), identifier(identifier), expression(std::move(expression)) {}

Assignment::~Assignment() = default;

const std::string& Assignment::getIdentifier() const { return identifier; }

const std::unique_ptr<Expression>& Assignment::getExpressionPtr() const { return expression; }

void Assignment::accept(InstructionVisitor& visitor) const { visitor.visit(*this); }

/* Printing */

Printing::Printing(std::unique_ptr<Expression>& expression)
    : Instruction(), expression(std::move(expression)) {}

Printing::~Printing() = default;

const std::unique_ptr<Expression>& Printing::getExpressionPtr() const { return expression; }

void Printing::accept(InstructionVisitor& visitor) const { visitor.visit(*this); }

/* InstructionVisitor */

InstructionVisitor::InstructionVisitor() = default;
InstructionVisitor::~InstructionVisitor() = default;

}  // namespace ast
}  // namespace cpmc
