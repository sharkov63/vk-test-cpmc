/** Beginning of Value.cpp */

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

class Value;
class StringValue;
class IntValue;
class FloatValue;

/**
 * Visitor interface for values.
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
 * Represents a possible value of a variable/constant in CPM.
 *
 * Any Value can be turned into string,
 * and any two Value instances can be added or subtracted.
 */
class Value {
   private:
    virtual Value* add(const Value& other) const = 0;
    virtual Value* sub(const Value& other) const = 0;

   public:
    Value() {}
    virtual ~Value() {}

    /**
     * Convert the Value to string.
     */
    virtual std::string toString() const = 0;

    /**
     * Take the sum (difference) of two Values.
     * Allocate resulting value in heap
     * and return pointer to it.
     *
     * Delegates the operation to add (sub).
     *
     * @return pointer to resulting Value.
     */
    Value* operator+(const Value& other) const { return add(other); }
    Value* operator-(const Value& other) const { return sub(other); }

    /**
     * Accepts given ValueVisitor.
     */
    virtual void accept(ValueVisitor& visitor) const = 0;
};

class StringValue : public Value {
   private:
    std::string value;

    class Adder : public ValueVisitor {
       private:
        const StringValue& lhs;
        Value* result;

       public:
        Adder(const StringValue& lhs) : lhs(lhs) {}
        virtual ~Adder() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        Value* getResult() const { return result; }
    };
    class Subtractor : public ValueVisitor {
       private:
        const StringValue& lhs;
        Value* result;

       public:
        Subtractor(const StringValue& lhs) : lhs(lhs) {}
        virtual ~Subtractor() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        Value* getResult() const { return result; }
    };

    virtual Value* add(const Value& other) const {
        Adder adder(*this);
        other.accept(adder);
        return adder.getResult();
    }
    virtual Value* sub(const Value& other) const {
        Subtractor subtractor(*this);
        other.accept(subtractor);
        return subtractor.getResult();
    }

   public:
    StringValue(const std::string& value) : Value(), value(value) {}
    virtual ~StringValue() {}

    virtual std::string toString() const { return value; }

    virtual void accept(ValueVisitor& visitor) const { visitor.visit(*this); }

    const std::string& getValue() const { return value; }

    int32_t toIntOrZero() const {
        int result;
        if (sscanf(value.c_str(), "%d", &result) != 1) {
            return 0;
        }
        return result;
    }

    float toFloatOrZero() const {
        float result;
        if (sscanf(value.c_str(), "%f", &result) != 1) {
            return 0;
        }
        return result;
    }
};

class IntValue : public Value {
   private:
    int32_t value;

    class Adder : public ValueVisitor {
       private:
        const IntValue& lhs;
        Value* result;

       public:
        Adder(const IntValue& lhs) : lhs(lhs) {}
        virtual ~Adder() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        Value* getResult() const { return result; }
    };
    class Subtractor : public ValueVisitor {
       private:
        const IntValue& lhs;
        Value* result;

       public:
        Subtractor(const IntValue& lhs) : lhs(lhs) {}
        virtual ~Subtractor() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        Value* getResult() const { return result; }
    };

    virtual Value* add(const Value& other) const {
        Adder adder(*this);
        other.accept(adder);
        return adder.getResult();
    }
    virtual Value* sub(const Value& other) const {
        Subtractor subtractor(*this);
        other.accept(subtractor);
        return subtractor.getResult();
    }

   public:
    IntValue(int32_t value) : Value(), value(value) {}
    virtual ~IntValue() {}

    virtual std::string toString() const {
        std::ostringstream temp;
        temp << value;
        return temp.str();
    }

    virtual void accept(ValueVisitor& visitor) const { visitor.visit(*this); }

    int32_t getValue() const { return value; }
};

class FloatValue : public Value {
   private:
    float value;

    class Adder : public ValueVisitor {
       private:
        const FloatValue& lhs;
        Value* result;

       public:
        Adder(const FloatValue& lhs) : lhs(lhs) {}
        virtual ~Adder() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        Value* getResult() const { return result; }
    };
    class Subtractor : public ValueVisitor {
       private:
        const FloatValue& lhs;
        Value* result;

       public:
        Subtractor(const FloatValue& lhs) : lhs(lhs) {}
        virtual ~Subtractor() {}

        virtual void visit(const StringValue& stringValue);
        virtual void visit(const IntValue& intValue);
        virtual void visit(const FloatValue& floatValue);

        Value* getResult() const { return result; }
    };

    virtual Value* add(const Value& other) const {
        Adder adder(*this);
        other.accept(adder);
        return adder.getResult();
    }
    virtual Value* sub(const Value& other) const {
        Subtractor subtractor(*this);
        other.accept(subtractor);
        return subtractor.getResult();
    }

   public:
    FloatValue(float value) : Value(), value(value) {}
    virtual ~FloatValue() {}

    virtual std::string toString() const {
        std::ostringstream temp;
        temp << value;
        return temp.str();
    }

    virtual void accept(ValueVisitor& visitor) const { visitor.visit(*this); }

    float getValue() const { return value; }
};

// Operations

void StringValue::Adder::visit(const StringValue& stringValue) {
    // Usual string concatenation
    result = new StringValue(lhs.getValue() + stringValue.getValue());
}

void StringValue::Adder::visit(const IntValue& intValue) {
    // Int is converted to string,
    // the usual string concatenation
    result = (Value*)(new StringValue(lhs.getValue() + intValue.toString()));
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
    result = new IntValue(lhs.toIntOrZero() - intValue.getValue());
}

void StringValue::Subtractor::visit(const FloatValue& floatValue) {
    // String is converted to float (or 0)
    result = new IntValue(lhs.toFloatOrZero() - floatValue.getValue());
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
    result = new IntValue(lhs.getValue() - stringValue.toIntOrZero());
}

void IntValue::Subtractor::visit(const IntValue& intValue) {
    // Usual int subtraction
    result = new IntValue(lhs.getValue() - intValue.getValue());
}

void IntValue::Subtractor::visit(const FloatValue& floatValue) {
    // Int is converted to float
    result = new FloatValue((float)lhs.getValue() + floatValue.getValue());
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

/** End of Value.cpp */

