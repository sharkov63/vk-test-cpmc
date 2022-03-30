#define BOOST_TEST_MODULE PrimitiveType_Test
#include "PrimitiveType.cpp"

#include <boost/test/included/unit_test.hpp>

#include "Debug.hpp"

namespace cpmc {
namespace runtime {

BOOST_AUTO_TEST_CASE(CONSTRUCTION) {
    PrimitiveType a = "abacaba";
    PrimitiveType b = 1337;
    PrimitiveType c = .55f;
    BOOST_TEST(a.toString() == "abacaba");
    BOOST_TEST(b.toString() == "1337");
    BOOST_TEST(c.toString() == "0.55");
}

BOOST_AUTO_TEST_CASE(ASSIGNMENT) {
    PrimitiveType a = "abacaba";
    a = 1;
    BOOST_TEST(a.toString() == "1");
    BOOST_TEST((a + 25).toString() == "26");
    a = 1.4f;
    BOOST_TEST(a.toString() == "1.4");
}

BOOST_AUTO_TEST_CASE(ADDITION) {
    PrimitiveType a = 1;
    PrimitiveType b = 0.5f;
    PrimitiveType c = "f";
    BOOST_TEST(((a + b) + c).toString() == "1.5f");
    BOOST_TEST((a + (b + c)).toString() == "10.5f");
    BOOST_TEST((a + a + a + a).toString() == "4");
}

BOOST_AUTO_TEST_CASE(SUBTRACTION) {
    PrimitiveType a = 5;
    PrimitiveType b = "54";
    PrimitiveType c = "c";
    PrimitiveType d = 1.1f;
    BOOST_TEST((b - a).toString() == "49");
    BOOST_TEST((c - a).toString() == "-5");
    BOOST_TEST((a - d).toString() == "3.9");
    BOOST_TEST((c - d).toString() == "-1.1");
}

BOOST_AUTO_TEST_CASE(NULL_TO_STRING) {
    PrimitiveType a;
    BOOST_TEST(a.toString() == "NULL");
}

}  // namespace runtime
}  // namespace cpmc
