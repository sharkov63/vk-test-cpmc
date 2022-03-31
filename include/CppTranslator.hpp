#ifndef CPMC_CPP_TRANSLATOR_INCLUDED
#define CPMC_CPP_TRANSLATOR_INCLUDED

#include "CppSourceCode.hpp"
#include "ast/Instruction.hpp"
#include "ast/Program.hpp"

namespace cpmc {

/**
 * Translates given ast::Program to CppSourceCode
 */
class CppTranslator {
   private:
    /**
     * src/runtime/Exception.cpp file as a C-String.
     */
    static const char RUNTIME_SOURCE_EXCEPTION_CPP[];
    /**
     * src/runtime/PrimitiveValue.cppp file as a C-String.
     */
    static const char RUNTIME_SOURCE_PRIMITIVE_VALUE_CPP[];
    /**
     * src/runtime/PrimitiveType.cpp file as a C-String.
     */
    static const char RUNTIME_SOURCE_PRIMITIVE_TYPE_CPP[];

    /**
     * CPM Program to translate.
     */
    const ast::Program& program;

    class MyInstructionVisitor : public ast::InstructionVisitor {
       private:
        std::ostream& stream;

       public:
        explicit MyInstructionVisitor(std::ostream& stream);
        virtual ~MyInstructionVisitor();

        virtual void visit(const ast::EmptyInstruction& emptyInstruction) override final;
        virtual void visit(const ast::Definition& definition) override final;
        virtual void visit(const ast::Assignment& assignment) override final;
        virtual void visit(const ast::Printing& printing) override final;
    };

   public:
    CppTranslator(const ast::Program& program);

    /**
     * Translates program to CppSourceCode.
     *
     * No-throw guarantee.
     */
    CppSourceCode translate();

    /**
     * Translates given CPM identifier
     * to a safe CPP identifier
     * by adding a prefix.
     *
     * This is done to ensure no identifer
     * collides with a CPP keyword.
     */
    static std::string translateIdentifier(const std::string& identifier);
};

}  // namespace cpmc

#endif  // CPMC_CPP_TRANSLATOR_INCLUDED include guard
