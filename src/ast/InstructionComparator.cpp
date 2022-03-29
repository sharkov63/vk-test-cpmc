#include "ast/InstructionComparator.hpp"

namespace cpmc {
namespace ast {

/* InstructionComparator */

InstructionComparator::InstructionComparator(const Instruction& instruction1, const Instruction& instruction2)
    : instruction1(instruction1), instruction2(instruction2) {}

InstructionComparator::~InstructionComparator() = default;

void InstructionComparator::visit(const EmptyInstruction& emptyInstruction) {
    EmptyInstructionComparator comparator(emptyInstruction);
    instruction2.accept(comparator);
    result = comparator.compare();
}

void InstructionComparator::visit(const Definition& definition) {
    DefinitionComparator comparator(definition);
    instruction2.accept(comparator);
    result = comparator.compare();
}

void InstructionComparator::visit(const Assignment& assignment) {
    AssignmentComparator comparator(assignment);
    instruction2.accept(comparator);
    result = comparator.compare();
}

void InstructionComparator::visit(const Printing& printing) {
    PrintingComparator comparator(printing);
    instruction2.accept(comparator);
    result = comparator.compare();
}

bool InstructionComparator::compare() {
    instruction1.accept(*this);
    return result;
}

/* EmptyInstructionComparator */

InstructionComparator::EmptyInstructionComparator::EmptyInstructionComparator(const EmptyInstruction& emptyInstruction)
    : emptyInstruction(emptyInstruction) {}

InstructionComparator::EmptyInstructionComparator::~EmptyInstructionComparator() = default;

void InstructionComparator::EmptyInstructionComparator::visit(const EmptyInstruction&) { result = true; }

void InstructionComparator::EmptyInstructionComparator::visit(const Definition&) { result = false; }

void InstructionComparator::EmptyInstructionComparator::visit(const Assignment&) { result = false; }

void InstructionComparator::EmptyInstructionComparator::visit(const Printing&) { result = false; }

bool InstructionComparator::EmptyInstructionComparator::compare() { return result; }

/* DefinitionComparator */

InstructionComparator::DefinitionComparator::DefinitionComparator(const Definition& definition)
    : definition(definition) {}

InstructionComparator::DefinitionComparator::~DefinitionComparator() = default;

void InstructionComparator::DefinitionComparator::visit(const EmptyInstruction&) { result = false; }

void InstructionComparator::DefinitionComparator::visit(const Definition& other) {
    result = definition.getKeyword() == other.getKeyword() && definition.getIdentifier() == other.getIdentifier() &&
             *definition.getExpressionPtr() == *other.getExpressionPtr();
}

void InstructionComparator::DefinitionComparator::visit(const Assignment&) { result = false; }

void InstructionComparator::DefinitionComparator::visit(const Printing&) { result = false; }

bool InstructionComparator::DefinitionComparator::compare() { return result; }

/* AssignmentComparator */

InstructionComparator::AssignmentComparator::AssignmentComparator(const Assignment& assignment)
    : assignment(assignment) {}

InstructionComparator::AssignmentComparator::~AssignmentComparator() = default;

void InstructionComparator::AssignmentComparator::visit(const EmptyInstruction&) { result = false; }

void InstructionComparator::AssignmentComparator::visit(const Definition&) { result = false; }

void InstructionComparator::AssignmentComparator::visit(const Assignment& other) {
    result = assignment.getIdentifier() == other.getIdentifier() &&
             *assignment.getExpressionPtr() == *other.getExpressionPtr();
}

void InstructionComparator::AssignmentComparator::visit(const Printing&) { result = false; }

bool InstructionComparator::AssignmentComparator::compare() { return result; }

/* PrintingComparator */

InstructionComparator::PrintingComparator::PrintingComparator(const Printing& printing) : printing(printing) {}

InstructionComparator::PrintingComparator::~PrintingComparator() = default;

void InstructionComparator::PrintingComparator::visit(const EmptyInstruction&) { result = false; }

void InstructionComparator::PrintingComparator::visit(const Definition&) { result = false; }

void InstructionComparator::PrintingComparator::visit(const Assignment&) { result = false; }

void InstructionComparator::PrintingComparator::visit(const Printing& other) {
    result = *printing.getExpressionPtr() == *other.getExpressionPtr();
}

bool InstructionComparator::PrintingComparator::compare() { return result; }

}  // namespace ast
}  // namespace cpmc
