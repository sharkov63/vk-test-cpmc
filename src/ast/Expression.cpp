#include "ast/Expression.hpp"

namespace cpmc {
    namespace ast {

        /* Expression */

        Expression::Expression(const ExpressionType& type):
            type(type) {}
        Expression::~Expression() = default;

        ExpressionType Expression::getType() const {
            return type;
        }


        /* LiteralExpression */

        LiteralExpression::LiteralExpression(const std::string& literal):
            Expression(ExpressionType::LITERAL),
            literal(literal) {}

        LiteralExpression::~LiteralExpression() {
            std::cerr << "Literal expression destructor" << literal << std::endl;
        }

        std::string LiteralExpression::toCppExpression() const {
            return literal;
        }

        bool LiteralExpression::operator==(const Expression& other) const {
            if (other.getType() != ExpressionType::LITERAL) {
                return false;
            }
            LiteralExpression* pointer = (LiteralExpression*)(&other);
            return literal == pointer->literal;
        }


        /* IdentifierExpression */

        IdentifierExpression::IdentifierExpression(const std::string& identifier):
            Expression(ExpressionType::IDENTIFIER),
            identifier(identifier) {}

        IdentifierExpression::~IdentifierExpression() = default;

        std::string IdentifierExpression::toCppExpression() const {
            return identifier;
        }

        bool IdentifierExpression::operator==(const Expression& other) const {
            if (other.getType() != ExpressionType::IDENTIFIER) {
                return false;
            }
            IdentifierExpression* pointer = (IdentifierExpression*)(&other);
            return identifier == pointer->identifier;
        }


        /* InputExpression */

        InputExpression::InputExpression():
            Expression(ExpressionType::INPUT),
            argument(std::unique_ptr<Expression>(new LiteralExpression("\"\""))) {}

        InputExpression::InputExpression(std::unique_ptr<Expression>& argument):
            Expression(ExpressionType::INPUT),
            argument(std::move(argument)) {}

        InputExpression::~InputExpression() = default;

        std::string InputExpression::toCppExpression() const {
            return "input(" + argument->toCppExpression() + ")";
        }

        bool InputExpression::operator==(const Expression& other) const {
            if (other.getType() != ExpressionType::INPUT) {
                return false;
            }
            InputExpression* pointer = (InputExpression*)(&other);
            return argument == pointer->argument;
        }


        /* OperationExpression */

        OperationExpression::OperationExpression(char operation,
                                                 std::unique_ptr<Expression>& lhs,
                                                 std::unique_ptr<Expression>& rhs):
            Expression(ExpressionType::OPERATION),
            operation(operation),
            lhs(std::move(lhs)),
            rhs(std::move(rhs)) {}

        OperationExpression::~OperationExpression() = default;

        std::string OperationExpression::toCppExpression() const {
            return "(" + lhs->toCppExpression() + ")" + operation + "(" + rhs->toCppExpression() + ")";
        }

        bool OperationExpression::operator==(const Expression& other) const {
            if (other.getType() != ExpressionType::OPERATION) {
                return false;
            }
            OperationExpression* pointer = (OperationExpression*)(&other);
            return lhs == pointer->lhs && rhs == pointer->rhs;
        }
    }
}
