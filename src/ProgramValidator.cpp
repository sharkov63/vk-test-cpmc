#include "ProgramValidator.hpp"

#include <cassert>
#include <map>
#include <set>

namespace cpmc {

/* ProgramValidatorResult */

ProgramValidatorResult::ProgramValidatorResult() : valid(true), errorMessage("") {}

ProgramValidatorResult::ProgramValidatorResult(const bool& valid, const std::string& errorMessage)
    : valid(valid), errorMessage(errorMessage) {}

/* ProgramValidator::MyInstructionVisitor */

ProgramValidator::MyInstructionVisitor::MyInstructionVisitor(ProgramValidator& validator)
    : ast::InstructionVisitor(), validator(validator) {}

void ProgramValidator::MyInstructionVisitor::visit(const ast::EmptyInstruction&) {
    if (!validator.currentResult.valid) return;
}

void ProgramValidator::MyInstructionVisitor::visit(const ast::Definition& definition) {
    if (!validator.currentResult.valid) return;
    const std::string& identifier = definition.getIdentifier();
    if (validator.isDeclared(identifier)) {
        // redefinition
        validator.currentResult.valid = false;
        validator.currentResult.errorMessage = "Redefinition of '" + identifier + "'.";
        return;
    }
    bool isConstant = definition.getKeyword() == "val";
    validator.declare(identifier, isConstant);
    const std::unique_ptr<ast::Expression>& eptr = definition.getExpressionPtr();
    if (eptr.get() == nullptr) {
        // declaration without definition
        return;
    }
    validator.validateExpression(*eptr);
    validator.define(identifier);
}

void ProgramValidator::MyInstructionVisitor::visit(const ast::Assignment& assignment) {
    if (!validator.currentResult.valid) return;
    const std::string& identifier = assignment.getIdentifier();
    if (!validator.isDeclared(identifier)) {
        // variable not defined
        validator.currentResult.valid = false;
        validator.currentResult.errorMessage = "Use of undeclared identifier '" + identifier + "'.";
        return;
    }
    validator.validateExpression(*assignment.getExpressionPtr());
    validator.define(identifier);
}

void ProgramValidator::MyInstructionVisitor::visit(const ast::Printing& printingInstruction) {
    if (!validator.currentResult.valid) return;
    validator.validateExpression(*printingInstruction.getExpressionPtr());
}

/* ProgramValidator */

void ProgramValidator::validateExpression(const ast::Expression& expression) {
    if (!currentResult.valid) return;

    ast::ExpressionType type = expression.getType();
    switch (type) {
        case ast::ExpressionType::STRING_LITERAL:
        case ast::ExpressionType::INT_LITERAL:
        case ast::ExpressionType::FLOAT_LITERAL: {
            return;
            break;
        }
        case ast::ExpressionType::IDENTIFIER: {
            ast::IdentifierExpression* eptr = (ast::IdentifierExpression*)&expression;
            std::string identifier = eptr->getIdentifier();
            ProgramValidator::validateIdentifierInExpression(identifier);
            break;
        }
        case ast::ExpressionType::INPUT: {
            ast::InputExpression* eptr = (ast::InputExpression*)&expression;
            validateExpression(*eptr->getArgument());
            break;
        }
        case ast::ExpressionType::OPERATION: {
            ast::OperationExpression* eptr = (ast::OperationExpression*)&expression;
            validateExpression(*eptr->getLhs());
            validateExpression(*eptr->getRhs());
            break;
        }
    }
}

void ProgramValidator::validateIdentifierInExpression(const std::string& identifier) {
    if (!currentResult.valid) return;

    if (defined.find(identifier) == defined.end()) {
        currentResult.valid = false;
        if (declaredIsConstant.find(identifier) != declaredIsConstant.end()) {
            currentResult.errorMessage = "Uninitialized variable '" + identifier + "' cannot be used in expression.";
        } else {
            currentResult.errorMessage = "Use of undeclared identifier '" + identifier + "'.";
        }
        return;
    }
}

ProgramValidator::ProgramValidator(const ast::Program& program) : program(program) {}

ProgramValidatorResult ProgramValidator::validate() {
    MyInstructionVisitor visitor(*this);
    for (const std::unique_ptr<ast::Instruction>& iptr : program.getInstructions()) {
        iptr->accept(visitor);
        if (!currentResult.valid) {
            break;
        }
    }
    return currentResult;
}

void ProgramValidator::declare(const std::string& identifier, bool isConstant) {
    assert(declaredIsConstant.find(identifier) == declaredIsConstant.end());
    declaredIsConstant[identifier] = isConstant;
}

void ProgramValidator::define(const std::string& identifier) { defined.insert(identifier); }

bool ProgramValidator::isDeclared(const std::string& identifier) const {
    return declaredIsConstant.find(identifier) != declaredIsConstant.end();
}

bool ProgramValidator::isDeclaredConstant(const std::string& identifier) const {
    auto iterator = declaredIsConstant.find(identifier);
    return iterator != declaredIsConstant.end() && iterator->second == true;
}

bool ProgramValidator::isDefined(const std::string& identifier) const {
    return defined.find(identifier) != defined.end();
}

}  // namespace cpmc
