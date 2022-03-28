#include "ast/Program.hpp"

namespace cpmc {
    namespace ast {

        Program::Program(const std::vector<std::unique_ptr<Instruction>>& instructions):
            instructions(instructions) {}
    }
}
