#include "ast/Expression.hpp"

namespace cpmc {
    namespace ast {

        /* Expression */

        Expression::Expression() = default;
        Expression::~Expression() = default;


        /* LiteralExpression */

        LiteralExpression::LiteralExpression(const std::string& literal):
            Expression(),
            literal(literal) {}

        LiteralExpression::~LiteralExpression() {
            std::cerr << "Literal expression destructor" << literal << std::endl;
        }

        std::string LiteralExpression::toCppExpression() const {
            return literal;
        }


        /* IdentifierExpression */

        IdentifierExpression::IdentifierExpression(const std::string& identifier):
            Expression(),
            identifier(identifier) {}

        IdentifierExpression::~IdentifierExpression() = default;

        std::string IdentifierExpression::toCppExpression() const {
            return identifier;
        }


        /* InputExpression */

        InputExpression::InputExpression():
            Expression(),
            argument(std::unique_ptr<Expression>(new LiteralExpression("\"\""))) {}

        InputExpression::InputExpression(std::unique_ptr<Expression>& argument):
            Expression(),
            argument(std::move(argument)) {}

        InputExpression::~InputExpression() = default;

        std::string InputExpression::toCppExpression() const {
            return "input(" + argument->toCppExpression() + ")";
        }


        /* OperationExpression */

        OperationExpression::OperationExpression(char operation,
                                                 std::unique_ptr<Expression>& lhs,
                                                 std::unique_ptr<Expression>& rhs):
            Expression(),
            operation(operation),
            lhs(std::move(lhs)),
            rhs(std::move(rhs)) {}

        OperationExpression::~OperationExpression() = default;

        std::string OperationExpression::toCppExpression() const {
            return "(" + lhs->toCppExpression() + ")" + operation + "(" + rhs->toCppExpression() + ")";
        }
    }
}
