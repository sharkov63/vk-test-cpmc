#ifndef CPMC_PROGRAM_VALIDATOR_INCLUDED
#define CPMC_PROGRAM_VALIDATOR_INCLUDED

#include <map>
#include <set>

#include "ast/Program.hpp"

namespace cpmc {

/**
 * Data class representing possible result
 * of Program Validation.
 */
class ProgramValidatorResult {
   public:
    bool valid;                /// Is the program valid
    std::string errorMessage;  /// If the program is not valid, where does the error happen.

    ProgramValidatorResult();
    ProgramValidatorResult(const bool& valid, const std::string& errorMessage);
};

/**
 * Validates ast::Program.
 * It ensures that:
 * - constant variables are not changed;
 * - all used identifiers are declared;
 * - all variables used in expressions are defined;
 */
class ProgramValidator {
   private:
    /**
     * Program to validate.
     */
    const ast::Program& program;

    /**
     * The keys are all declared identifiers (variables).
     * The value of an identifier is true iff
     * the corresponding variable is a constant.
     */
    std::map<std::string, bool> declaredIsConstant;

    /**
     * Contains all defined variables,
     * i.e. all variables which have
     * their assigned value.
     */
    std::set<std::string> defined;

    /**
     * Validator of instructions implemented
     * as ast::InstructionVisitor.
     */
    class MyInstructionVisitor : public ast::InstructionVisitor {
       private:
        ProgramValidator& validator;

       public:
        MyInstructionVisitor(ProgramValidator& validator);

        virtual void visit(const ast::EmptyInstruction& emptyInstruction) override final;
        virtual void visit(const ast::Definition& definition) override final;
        virtual void visit(const ast::Assignment& assignment) override final;
        virtual void visit(const ast::Printing& printingInstruction) override final;
    };

    /**
     * Validates expression.
     */
    void validateExpression(const ast::Expression& expression);

    /**
     * Validates identifier inside an expression.
     */
    void validateIdentifierInExpression(const std::string& identifier);

   public:
    ProgramValidator(const ast::Program& program);

    /**
     * Validate given program.
     *
     * No-throw guarantee.
     */
    ProgramValidatorResult validate();

    void declare(const std::string& identifier, bool isConstant);
    void define(const std::string& identifier);

    bool isDeclared(const std::string& identifier) const;
    bool isDeclaredConstant(const std::string& identifier) const;
    bool isDefined(const std::string& identifier) const;

    /**
     * Current result at the moment;
     */
    ProgramValidatorResult currentResult;
};

}  // namespace cpmc

#endif  // CPMC_PROGRAM_VALIDATOR_INCLUDED include guard
