#define BOOST_TEST_MODULE Value_Test

#include "Value.cpp"

#include <boost/test/included/unit_test.hpp>

namespace cpmc {
namespace runtime {

BOOST_AUTO_TEST_CASE(STRING_PLUS_STRING) {
    StringValue s1("Hello");
    StringValue s2("!");
    std::unique_ptr<StringValue> res((StringValue*)(s1 + s2));
    BOOST_TEST(res->getValue() == "Hello!");
}

BOOST_AUTO_TEST_CASE(THREE_INT_SUM) {
    IntValue i1(21);
    IntValue i2(2);
    IntValue i3(18);
    std::unique_ptr<IntValue> i12((IntValue*)(i1 + i2));
    std::unique_ptr<IntValue> res((IntValue*)(*i12 + i3));
    BOOST_TEST(res->getValue() == 41);
}

BOOST_AUTO_TEST_CASE(STRING_PLUS_INT) {
    StringValue s("World");
    IntValue i(42);
    std::unique_ptr<StringValue> res((StringValue*)(s + i));
    BOOST_TEST(res->getValue() == "World42");
}

BOOST_AUTO_TEST_CASE(STRING_MINUS_INT) {
    StringValue s("World");
    IntValue i(42);
    std::unique_ptr<IntValue> res((IntValue*)(s - i));
    BOOST_TEST(res->getValue() == -42);
}

BOOST_AUTO_TEST_CASE(FLOAT_PLUS_INT) {
    FloatValue pi(3.14);
    IntValue answerNumber(42);
    std::unique_ptr<FloatValue> res((FloatValue*)(pi + answerNumber));
    BOOST_TEST(fabs(res->getValue() - 45.14) < 0.01);
}

BOOST_AUTO_TEST_CASE(NUMBER_STRING_PLUS_INT) {
    StringValue numberString("134");
    IntValue answerNumber(42);
    std::unique_ptr<StringValue> res((StringValue*)(numberString + answerNumber));
    BOOST_TEST(res->getValue() == "13442");
}

BOOST_AUTO_TEST_CASE(NUMBER_STRING_MINUS_INT) {
    StringValue numberString("134");
    IntValue answerNumber(42);
    std::unique_ptr<IntValue> res((IntValue*)(numberString - answerNumber));
    BOOST_TEST(res->getValue() == 92);
}

}  // namespace runtime
}  // namespace cpmc
