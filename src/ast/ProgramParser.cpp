#include "ast/ProgramParser.hpp"

#include "ast/InstructionComparator.hpp"

namespace cpmc {
namespace ast {

ProgramParser::ProgramParser(ParsingContext& context)
    : context(context), instructionParser(InstructionParser(context)) {}

Program ProgramParser::parse() {
    std::vector<std::unique_ptr<Instruction>> instructions;
    while (!context.done()) {
        std::unique_ptr<Instruction> instruction = instructionParser.nextInstruction();
        EmptyInstruction emptyInstruction;
        InstructionComparator comparator(emptyInstruction, *instruction);
        if (comparator.compare()) {
            // empty instruction
            continue;
        }
        instructions.push_back(std::move(instruction));
    }
    return Program(std::move(instructions));
}

}  // namespace ast
}  // namespace cpmc
