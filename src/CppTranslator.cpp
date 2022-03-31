#include "CppTranslator.hpp"

#include <cassert>
#include <sstream>

#include "ast/Expression.hpp"
#include "ast/Instruction.hpp"

namespace cpmc {

/* CppTranslator::MyInstructionVisitor */

CppTranslator::MyInstructionVisitor::MyInstructionVisitor(std::ostream& stream)
    : InstructionVisitor(), stream(stream) {}

CppTranslator::MyInstructionVisitor::~MyInstructionVisitor() = default;

void CppTranslator::MyInstructionVisitor::visit(const ast::EmptyInstruction&) {}

void CppTranslator::MyInstructionVisitor::visit(const ast::Definition& definition) {
    if (definition.getKeyword() == "val") {
        stream << "const ";
    } else {
        assert(definition.getKeyword() == "var");
    }
    stream << "cpmc::runtime::PrimitiveType " << translateIdentifier(definition.getIdentifier());
    const std::unique_ptr<ast::Expression>& eptr = definition.getExpressionPtr();
    if (eptr.get() == nullptr) {
        // declaration without definition
        assert(definition.getKeyword() == "var");
        return;
    }
    stream << " = " << definition.getExpressionPtr()->toCppExpression();
}

void CppTranslator::MyInstructionVisitor::visit(const ast::Assignment& assignment) {
    stream << translateIdentifier(assignment.getIdentifier());
    stream << " = " << assignment.getExpressionPtr()->toCppExpression();
}

void CppTranslator::MyInstructionVisitor::visit(const ast::Printing& printing) {
    stream << "cpmc::runtime::PrimitiveType::print(";
    stream << printing.getExpressionPtr()->toCppExpression();
    stream << ")";
}

/* CppTranslator */

CppTranslator::CppTranslator(const ast::Program& program) : program(program) {}

CppSourceCode CppTranslator::translate() {
    std::ostringstream s;

    MyInstructionVisitor visitor(s);

    s << RUNTIME_SOURCE_EXCEPTION_CPP << '\n';
    s << RUNTIME_SOURCE_PRIMITIVE_VALUE_CPP << '\n';
    s << RUNTIME_SOURCE_PRIMITIVE_TYPE_CPP << '\n';
    s << "\n\n\n\n";
    s << "int main() {                       \n";

    for (const std::unique_ptr<ast::Instruction>& iptr : program.getInstructions()) {
        s << "    ";            // indent
        iptr->accept(visitor);  // print instruction
        s << ";\n";             // new line
    }

    s << "    return 0;                      \n";
    s << "}                                  \n";

    return s.str();
}

std::string CppTranslator::translateIdentifier(const std::string& identifier) { return "cpm_id_" + identifier; }

}  // namespace cpmc
