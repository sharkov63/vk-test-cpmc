#ifndef CPMC_PRIMITIVE_TYPE_RUNTIME_INCLUDED
#define CPMC_PRIMITIVE_TYPE_RUNTIME_INCLUDED

/** Beginning of PrimitiveType.cpp */

/**
 * This CPP file will be inserted in
 * every translated-into-CPP CPM code,
 * so it combines both declaration
 * and implementation and does not have
 * corresponding header file.
 *
 * Also, in order to not depend on C++11
 * standard, it does not utilize
 * stuff like std::unique_ptr and etc.
 */

#include <iostream>
#include <sstream>

#ifdef CPMC_BUILD
// included only for unit-testing,
// should not be included while compiling
// CPM code
#include "Exception.cpp"
#include "PrimitiveValue.cpp"
#endif

namespace cpmc {
namespace runtime {

/**
 * A PrimitiveType in CPM language.
 *
 * Basically it owns a pointer to PrimitiveValue,
 * which is allocated in heap.
 */
class PrimitiveType {
   private:
    /**
     * Null if not initialized.
     */
    PrimitiveValue* value;

   public:
    PrimitiveType() : value(nullptr) {}
    explicit PrimitiveType(PrimitiveValue* value) : value(value) {}
    PrimitiveType(const std::string& s) : value(new StringValue(s)) {}
    PrimitiveType(const char* c) : value(new StringValue(c)) {}
    PrimitiveType(int32_t x) : value(new IntValue(x)) {}
    PrimitiveType(float x) : value(new FloatValue(x)) {}
    PrimitiveType(const PrimitiveType& other) : value(other.value->clone()) {}
    ~PrimitiveType() { delete value; }

    PrimitiveType& operator=(const PrimitiveType& other) {
        PrimitiveType tmp(other);
        swap(tmp);
        return *this;
    }

    PrimitiveType operator+(const PrimitiveType& other) const { return PrimitiveType(value->add(*other.value)); }

    PrimitiveType operator-(const PrimitiveType& other) const { return PrimitiveType(value->sub(*other.value)); }

    /**
     * May return null.
     */
    PrimitiveValue* getPointer() const { return value; }

    std::string toString() const {
        if (value == nullptr) {
            return "NULL";
        }
        return value->toString();
    }

    friend std::ostream& operator<<(std::ostream& stream, const PrimitiveType& variable);

    void swap(PrimitiveType& other) { std::swap(value, other.value); }

    static void print(std::ostream& stream, const PrimitiveType& x) { stream << x << std::endl; }

    static void print(const PrimitiveType& x) { print(std::cout, x); }

    static PrimitiveType input(std::istream& in, std::ostream& out, const std::string& message) {
        out << message;
        std::string s;
        in >> s;
        return s;
    }

    static PrimitiveType input(const std::string& message) { return input(std::cin, std::cout, message); }

    static PrimitiveType input() { return input(std::cin, std::cout, ""); }
};

std::ostream& operator<<(std::ostream& stream, const PrimitiveType& variable) { return stream << variable.toString(); }

}  // namespace runtime
}  // namespace cpmc

/** End of PrimitiveType.cpp */

#endif  // CPMC_PRIMITIVE_TYPE_RUNTIME_INCLUDED include guard
