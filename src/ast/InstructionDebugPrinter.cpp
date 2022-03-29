#include "ast/InstructionDebugPrinter.hpp"

namespace cpmc {
namespace ast {

InstructionDebugPrinter::InstructionDebugPrinter(std::ostream& stream) : stream(stream) {}

InstructionDebugPrinter::~InstructionDebugPrinter() = default;

void InstructionDebugPrinter::visit(const EmptyInstruction&) { stream << ";"; }

void InstructionDebugPrinter::visit(const Definition& definition) {
    stream << definition.getKeyword() << " " << definition.getIdentifier() << " = (" << *definition.getExpressionPtr()
           << ")" << std::endl;
}

void InstructionDebugPrinter::visit(const Assignment& assignment) {
    stream << assignment.getIdentifier() << " = (" << *assignment.getExpressionPtr() << ")" << std::endl;
}

void InstructionDebugPrinter::visit(const Printing& printing) {
    stream << "print(" << *printing.getExpressionPtr() << ")";
}

}  // namespace ast
}  // namespace cpmc
