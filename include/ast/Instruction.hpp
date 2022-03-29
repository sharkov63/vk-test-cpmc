#ifndef CPMC_AST_INSTRUCTION_HPP_INCLUDED
#define CPMC_AST_INSTRUCTION_HPP_INCLUDED

#include <memory>
#include <string>

#include "ast/Expression.hpp"

namespace cpmc {
namespace ast {

/**
 * See below.
 */
class InstructionVisitor;

/**
 * A single instruction in CPM language.
 */
class Instruction {
   public:
    Instruction();
    virtual ~Instruction();

    /**
     * Accepts given visitor.
     */
    virtual void accept(InstructionVisitor& visitor) const = 0;
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

    virtual void accept(InstructionVisitor& visitor) const override;
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
    Definition(const std::string& keyword, const std::string& identifier);

    Definition(const std::string& keyword, const std::string& identifier,
               std::unique_ptr<Expression>& expression);

    virtual ~Definition() override;

    virtual void accept(InstructionVisitor& visitor) const override;
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

    virtual void accept(InstructionVisitor& visitor) const override;
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

    virtual void accept(InstructionVisitor& visitor) const override;
};

/**
 * Vistor interface for Instructions.
 */
class InstructionVisitor {
   public:
    InstructionVisitor();
    virtual ~InstructionVisitor();

    virtual void visit(const EmptyInstruction& emptyInstruction) = 0;
    virtual void visit(const Definition& definition) = 0;
    virtual void visit(const Assignment& assignment) = 0;
    virtual void visit(const Printing& printingInstruction) = 0;
};

}  // namespace ast
}  // namespace cpmc

#endif  // CPMC_AST_INSTRUCTION_HPP_INCLUDED include guard
