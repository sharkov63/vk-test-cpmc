#ifndef CPMC_PRIMITIVE_VALUE_RUNTIME_INCLUDED
#define CPMC_PRIMITIVE_VALUE_RUNTIME_INCLUDED

/** Beginning of PrimitiveValue.cpp */

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

#include <memory>
#include <sstream>
#include <string>

namespace cpmc {
namespace runtime {

class PrimitiveValue;
class StringValue;
class IntValue;
class FloatValue;

/**
 * Visitor interface for PrimitveValues.
 */
class ValueVisitor {
   public:
    ValueVisitor() {}
    virtual ~ValueVisitor() {}
    virtual void visit(const StringValue& stringValue) = 0;
    virtual void visit(const IntValue& intValue) = 0;
    virtual void visit(const FloatValue& floatValue) = 0;
};

/**
 * Stores actual value of a CPM variable/expression.
 *
 * Any PrimitiveValue can be turned into string,
 * and any two PrimitiveValues can be added or subtracted.
 *
 * One should not directly use following classes
 * and instead work with PrimitiveType.
 */
class PrimitiveValue {
   public:
    PrimitiveValue() {}
    virtual ~PrimitiveValue() {}

    /**
     * Convert the PrimitiveValue to string.
     */
    virtual std::string toString() const = 0;

    /**
     * Take the sum (difference) of two PrimitiveValues.
     * Allocate resulting value in heap
     * and return pointer to it.
     *
     * @return pointer to resulting PrimitiveValue.
     */
    virtual PrimitiveValue* add(const PrimitiveValue& other) const = 0;
    virtual PrimitiveValue* sub(const PrimitiveValue& other) const = 0;

    /**
     * Accepts given ValueVisitor.
     */
    virtual void accept(ValueVisitor& visitor) const = 0;

    /**
     * Make a copy of this value
     * and allocate the copy in heap.
     */
    virtual PrimitiveValue* clone() const = 0;
};

class StringValue : public PrimitiveValue {
   private:
    std::string value;

    class Adder : public ValueVisitor {
       private:
        const StringValue& lhs;
        PrimitiveValue* result;

       public:
        Adder(const StringValue& lhs) : lhs(lhs) {}
        virtual ~Adder() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        PrimitiveValue* getResult() const { return result; }
    };
    class Subtractor : public ValueVisitor {
       private:
        const StringValue& lhs;
        PrimitiveValue* result;

       public:
        Subtractor(const StringValue& lhs) : lhs(lhs) {}
        virtual ~Subtractor() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        PrimitiveValue* getResult() const { return result; }
    };

   public:
    StringValue(const std::string& value) : PrimitiveValue(), value(value) {}
    virtual ~StringValue() {}

    virtual std::string toString() const { return value; }

    virtual PrimitiveValue* add(const PrimitiveValue& other) const {
        Adder adder(*this);
        other.accept(adder);
        return adder.getResult();
    }
    virtual PrimitiveValue* sub(const PrimitiveValue& other) const {
        Subtractor subtractor(*this);
        other.accept(subtractor);
        return subtractor.getResult();
    }

    virtual void accept(ValueVisitor& visitor) const { visitor.visit(*this); }

    const std::string& getValue() const { return value; }

    int32_t toIntOrZero() const {
        const char* strBegin = value.c_str();
        char* strEnd;
        int result = std::strtol(strBegin, &strEnd, 10);
        if (result == 0 || strEnd - strBegin < (long)value.size()) {
            return 0;
        }
        return result;
    }

    float toFloatOrZero() const {
        const char* strBegin = value.c_str();
        char* strEnd;
        float result = std::strtof(strBegin, &strEnd);
        if (result == 0 || strEnd - strBegin < (long)value.size()) {
            return 0;
        }
        return result;
    }

    virtual PrimitiveValue* clone() const { return new StringValue(value); }
};

class IntValue : public PrimitiveValue {
   private:
    int32_t value;

    class Adder : public ValueVisitor {
       private:
        const IntValue& lhs;
        PrimitiveValue* result;

       public:
        Adder(const IntValue& lhs) : lhs(lhs) {}
        virtual ~Adder() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        PrimitiveValue* getResult() const { return result; }
    };
    class Subtractor : public ValueVisitor {
       private:
        const IntValue& lhs;
        PrimitiveValue* result;

       public:
        Subtractor(const IntValue& lhs) : lhs(lhs) {}
        virtual ~Subtractor() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        PrimitiveValue* getResult() const { return result; }
    };

   public:
    IntValue(int32_t value) : PrimitiveValue(), value(value) {}
    virtual ~IntValue() {}

    virtual std::string toString() const {
        std::ostringstream temp;
        temp << value;
        return temp.str();
    }

    virtual PrimitiveValue* add(const PrimitiveValue& other) const {
        Adder adder(*this);
        other.accept(adder);
        return adder.getResult();
    }
    virtual PrimitiveValue* sub(const PrimitiveValue& other) const {
        Subtractor subtractor(*this);
        other.accept(subtractor);
        return subtractor.getResult();
    }

    virtual void accept(ValueVisitor& visitor) const { visitor.visit(*this); }

    int32_t getValue() const { return value; }

    virtual PrimitiveValue* clone() const { return new IntValue(value); }
};

class FloatValue : public PrimitiveValue {
   private:
    float value;

    class Adder : public ValueVisitor {
       private:
        const FloatValue& lhs;
        PrimitiveValue* result;

       public:
        Adder(const FloatValue& lhs) : lhs(lhs) {}
        virtual ~Adder() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        PrimitiveValue* getResult() const { return result; }
    };
    class Subtractor : public ValueVisitor {
       private:
        const FloatValue& lhs;
        PrimitiveValue* result;

       public:
        Subtractor(const FloatValue& lhs) : lhs(lhs) {}
        virtual ~Subtractor() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        PrimitiveValue* getResult() const { return result; }
    };

   public:
    FloatValue(float value) : PrimitiveValue(), value(value) {}
    virtual ~FloatValue() {}

    virtual std::string toString() const {
        std::ostringstream temp;
        temp << value;
        return temp.str();
    }

    virtual PrimitiveValue* add(const PrimitiveValue& other) const {
        Adder adder(*this);
        other.accept(adder);
        return adder.getResult();
    }
    virtual PrimitiveValue* sub(const PrimitiveValue& other) const {
        Subtractor subtractor(*this);
        other.accept(subtractor);
        return subtractor.getResult();
    }

    virtual void accept(ValueVisitor& visitor) const { visitor.visit(*this); }

    float getValue() const { return value; }

    virtual PrimitiveValue* clone() const { return new FloatValue(value); }
};

// Operations

void StringValue::Adder::visit(const StringValue& stringValue) {
    // Usual string concatenation
    result = new StringValue(lhs.getValue() + stringValue.getValue());
}

void StringValue::Adder::visit(const IntValue& intValue) {
    // Int is converted to string,
    // the usual string concatenation
    result = (PrimitiveValue*)(new StringValue(lhs.getValue() + intValue.toString()));
}

void StringValue::Adder::visit(const FloatValue& floatValue) {
    // Float is converted to string,
    // the usual string concatenation
    result = new StringValue(lhs.getValue() + floatValue.toString());
}

void StringValue::Subtractor::visit(const StringValue&) {
    // Unspecified
    result = new StringValue("");
}

void StringValue::Subtractor::visit(const IntValue& intValue) {
    // String is converted to int (or 0)
    result = new IntValue((int32_t)lhs.toFloatOrZero() - intValue.getValue());
}

void StringValue::Subtractor::visit(const FloatValue& floatValue) {
    // String is converted to float (or 0)
    result = new FloatValue(lhs.toFloatOrZero() - floatValue.getValue());
}

void IntValue::Adder::visit(const StringValue& stringValue) {
    // Int is converted to string,
    // the usual string concatenation
    result = new StringValue(lhs.toString() + stringValue.getValue());
}

void IntValue::Adder::visit(const IntValue& intValue) {
    // Usual int addition
    result = new IntValue(lhs.getValue() + intValue.getValue());
}

void IntValue::Adder::visit(const FloatValue& floatValue) {
    // Int is converted to float
    result = new FloatValue((float)lhs.getValue() + floatValue.getValue());
}

void IntValue::Subtractor::visit(const StringValue& stringValue) {
    // String is converted to int (or 0)
    result = new IntValue(lhs.getValue() - (int32_t)stringValue.toFloatOrZero());
}

void IntValue::Subtractor::visit(const IntValue& intValue) {
    // Usual int subtraction
    result = new IntValue(lhs.getValue() - intValue.getValue());
}

void IntValue::Subtractor::visit(const FloatValue& floatValue) {
    // Int is converted to float
    result = new FloatValue((float)lhs.getValue() - floatValue.getValue());
}

void FloatValue::Adder::visit(const StringValue& stringValue) {
    // Float is converted to string,
    // the usual string concatenation
    result = new StringValue(lhs.toString() + stringValue.getValue());
}

void FloatValue::Adder::visit(const IntValue& intValue) {
    // Int is converted to float
    result = new FloatValue(lhs.getValue() + (float)intValue.getValue());
}

void FloatValue::Adder::visit(const FloatValue& floatValue) {
    // Usual float addition
    result = new FloatValue(lhs.getValue() + floatValue.getValue());
}

void FloatValue::Subtractor::visit(const StringValue& stringValue) {
    // String is converted to float (or 0)
    result = new FloatValue(lhs.getValue() - stringValue.toFloatOrZero());
}

void FloatValue::Subtractor::visit(const IntValue& intValue) {
    // Int is converted to float
    result = new FloatValue(lhs.getValue() - (float)intValue.getValue());
}

void FloatValue::Subtractor::visit(const FloatValue& floatValue) {
    // Usual float subtraction
    result = new FloatValue(lhs.getValue() - floatValue.getValue());
}

}  // namespace runtime
}  // namespace cpmc

/** End of PrimitiveValue.cpp */

#endif  // CPMC_PRIMITIVE_VALUE_RUNTIME_INCLUDED include guard
