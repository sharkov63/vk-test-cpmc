#ifndef CPMC_AST_INSTRUCTION_HPP_INCLUDED
#define CPMC_AST_INSTRUCTION_HPP_INCLUDED

#include "ast/Expression.hpp"

#include <string>
#include <memory>

namespace cpmc {
    namespace ast {

        /**
         * Possible types of Instruction.
         */
        enum InstructionType {
            EMPTY_INSTRUCTION,      /// Unlike Expression, an Instruction can be empty, which means it does nothing. Usually skipped.
            DEFINITION,             /// Creates and optionally assigns a variable (or a constant).
            ASSIGNMENT,             /// Assigns a value to a variable.
            PRINTING,               /// Prints an expression to standard output.
        };
        
        /**
         * A single instruction in CPM language.
         */
        class Instruction {
            private:
                /**
                 * The type of Instruction;
                 *
                 * MUST ALWAYS MATCH WITH THE DERIVED CLASS OF INSTRUCTION.
                 */
                const InstructionType type;

            public:
                Instruction(const InstructionType& type);
                virtual ~Instruction();
        };


        /**
         * "Do nothing" instruction.
         * Usually skipped in Program.
         *
         * Unlike Expression, an Instruction can be empty.
         *
         * In CPM source code it is either an empty space between
         * two semicolons, or an unused expression.
         */
        class EmptyInstruction : public Instruction {
            public:
                EmptyInstruction();
                virtual ~EmptyInstruction() override;
        };


        /**
         * Create and define a variable (or a constant).
         *
         * In CPM source code it may look in following ways:
         * - <val/var> <identifier> = <expression>;
         * - var <identifier>;
         */
        class Definition : public Instruction {
            private:
                /**
                 * Definiton keyword.
                 *
                 * Either "var" or "val".
                 */
                const std::string keyword;

                /**
                 * The name of the created variable (constant).
                 */
                const std::string identifier;

                /**
                 * An expression which initializes that variable (constant).
                 *
                 * If the variable is declared without definition,
                 * then this points to nullptr. 
                 */
                const std::unique_ptr<Expression> expression;

            public:
                Definition(const std::string& keyword,
                           const std::string& identifier);

                Definition(const std::string& keyword,
                           const std::string& identifier,
                           std::unique_ptr<Expression>& expression);

                virtual ~Definition() override;

        };

    
        /**
         * Assigns value to a variable.
         *
         * In CPM source code it looks like:
         * <identifier> = <expression>;
         */
        class Assignment : public Instruction {
            private:
                /**
                 * The name of the variable to assign.
                 */
                const std::string identifier;

                /**
                 * The value to assign.
                 *
                 * Can not be nullptr.
                 */
                const std::unique_ptr<Expression> expression;

            public:
                Assignment(const std::string& identifier,
                           std::unique_ptr<Expression>& expression);

                virtual ~Assignment() override;
        };


        /**
         * Prints and expression to standard output.
         */
        class Printing : public Instruction {
            private:
                /**
                 * Expression to print.
                 */
                const std::unique_ptr<Expression> expression;

            public:
                Printing(std::unique_ptr<Expression>& expression);

                virtual ~Printing() override;
        };
    }
}


#endif  // CPMC_AST_INSTRUCTION_HPP_INCLUDED include guard
