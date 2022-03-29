#define BOOST_TEST_MODULE Tokenizer_Test
#include "Tokenizer.hpp"

#include <boost/test/included/unit_test.hpp>

#include "Debug.hpp"
#include "Exception.hpp"

namespace cpmc {

void singleTest(const std::string& src, const std::vector<Token>& expected) {
    auto calculated = Tokenizer(src).tokenize();
    BOOST_TEST(expected == calculated);
}

BOOST_AUTO_TEST_CASE(VK_STATEMENT_TESTS) {
    singleTest("var str = \"Hello\";", {
                                           {KEYWORD, "var"},
                                           {IDENTIFIER, "str"},
                                           {OPERATOR, "="},
                                           {STRING_LITERAL, "\"Hello\""},
                                           {DELIMITER, ";"},
                                       });

    singleTest("str = str + \"!\";", {
                                         {IDENTIFIER, "str"},
                                         {OPERATOR, "="},
                                         {IDENTIFIER, "str"},
                                         {OPERATOR, "+"},
                                         {STRING_LITERAL, "\"!\""},
                                         {DELIMITER, ";"},
                                     });

    singleTest("print(str);", {
                                  {KEYWORD, "print"},
                                  {DELIMITER, "("},
                                  {IDENTIFIER, "str"},
                                  {DELIMITER, ")"},
                                  {DELIMITER, ";"},
                              });

    singleTest("str = 21 + 2 + 18;", {
                                         {IDENTIFIER, "str"},
                                         {OPERATOR, "="},
                                         {INT_LITERAL, "21"},
                                         {OPERATOR, "+"},
                                         {INT_LITERAL, "2"},
                                         {OPERATOR, "+"},
                                         {INT_LITERAL, "18"},
                                         {DELIMITER, ";"},
                                     });

    singleTest("print(str);         // -> 42", {
                                                   {KEYWORD, "print"},
                                                   {DELIMITER, "("},
                                                   {IDENTIFIER, "str"},
                                                   {DELIMITER, ")"},
                                                   {DELIMITER, ";"},
                                               });

    singleTest("val worldString = \"World\";\n", {
                                                     {KEYWORD, "val"},
                                                     {IDENTIFIER, "worldString"},
                                                     {OPERATOR, "="},
                                                     {STRING_LITERAL, "\"World\""},
                                                     {DELIMITER, ";"},
                                                 });

    singleTest("val answerNumber = 42;\n", {
                                               {KEYWORD, "val"},
                                               {IDENTIFIER, "answerNumber"},
                                               {OPERATOR, "="},
                                               {INT_LITERAL, "42"},
                                               {DELIMITER, ";"},
                                           });

    singleTest("print(worldString + answerNumber); // -> World42", {
                                                                       {KEYWORD, "print"},
                                                                       {DELIMITER, "("},
                                                                       {IDENTIFIER, "worldString"},
                                                                       {OPERATOR, "+"},
                                                                       {IDENTIFIER, "answerNumber"},
                                                                       {DELIMITER, ")"},
                                                                       {DELIMITER, ";"},
                                                                   });

    singleTest("print(worldString - answerNumber); // -> -42", {
                                                                   {KEYWORD, "print"},
                                                                   {DELIMITER, "("},
                                                                   {IDENTIFIER, "worldString"},
                                                                   {OPERATOR, "-"},
                                                                   {IDENTIFIER, "answerNumber"},
                                                                   {DELIMITER, ")"},
                                                                   {DELIMITER, ";"},
                                                               });

    singleTest("val pi = 3.14;", {
                                     {KEYWORD, "val"},
                                     {IDENTIFIER, "pi"},
                                     {OPERATOR, "="},
                                     {FLOAT_LITERAL, "3.14"},
                                     {DELIMITER, ";"},
                                 });

    singleTest("print(pi + answerNumber); // -> 45.14", {
                                                            {KEYWORD, "print"},
                                                            {DELIMITER, "("},
                                                            {IDENTIFIER, "pi"},
                                                            {OPERATOR, "+"},
                                                            {IDENTIFIER, "answerNumber"},
                                                            {DELIMITER, ")"},
                                                            {DELIMITER, ";"},
                                                        });

    singleTest("val numberString = \"134\";", {
                                                  {KEYWORD, "val"},
                                                  {IDENTIFIER, "numberString"},
                                                  {OPERATOR, "="},
                                                  {STRING_LITERAL, "\"134\""},
                                                  {DELIMITER, ";"},
                                              });

    singleTest("print(numberString + answerNumber); // -> 92", {
                                                                   {KEYWORD, "print"},
                                                                   {DELIMITER, "("},
                                                                   {IDENTIFIER, "numberString"},
                                                                   {OPERATOR, "+"},
                                                                   {IDENTIFIER, "answerNumber"},
                                                                   {DELIMITER, ")"},
                                                                   {DELIMITER, ";"},
                                                               });

    singleTest("print(numberString - answerNumber); // -> 13442", {
                                                                      {KEYWORD, "print"},
                                                                      {DELIMITER, "("},
                                                                      {IDENTIFIER, "numberString"},
                                                                      {OPERATOR, "-"},
                                                                      {IDENTIFIER, "answerNumber"},
                                                                      {DELIMITER, ")"},
                                                                      {DELIMITER, ";"},
                                                                  });

    singleTest("val name = input(\"Name: \"); // prints \"Name: \" and waits for input",
               {
                   {KEYWORD, "val"},
                   {IDENTIFIER, "name"},
                   {OPERATOR, "="},
                   {KEYWORD, "input"},
                   {DELIMITER, "("},
                   {STRING_LITERAL, "\"Name: \""},
                   {DELIMITER, ")"},
                   {DELIMITER, ";"},
               });

    singleTest("print(\"Your name is \" + name);", {
                                                       {KEYWORD, "print"},
                                                       {DELIMITER, "("},
                                                       {STRING_LITERAL, "\"Your name is \""},
                                                       {OPERATOR, "+"},
                                                       {IDENTIFIER, "name"},
                                                       {DELIMITER, ")"},
                                                       {DELIMITER, ";"},
                                                   });
}

BOOST_AUTO_TEST_CASE(BLANKS) {
    singleTest("", {});
    singleTest("   \n \n     \n ", {});
    singleTest(" \f\n\r\t\v", {});
}

BOOST_AUTO_TEST_CASE(MISC) {
    singleTest("  var  inputj=   input(\"print\");  ;      ;   ", {
                                                                      {KEYWORD, "var"},
                                                                      {IDENTIFIER, "inputj"},
                                                                      {OPERATOR, "="},
                                                                      {KEYWORD, "input"},
                                                                      {DELIMITER, "("},
                                                                      {STRING_LITERAL, "\"print\""},
                                                                      {DELIMITER, ")"},
                                                                      {DELIMITER, ";"},
                                                                      {DELIMITER, ";"},
                                                                      {DELIMITER, ";"},
                                                                  });
    return;

    singleTest("    \"// not a comment\"   // a comment   ",
               {
                   {STRING_LITERAL, "\"// not a comment\""},
               });

    singleTest("(()))", {
                            {DELIMITER, "("},
                            {DELIMITER, "("},
                            {DELIMITER, ")"},
                            {DELIMITER, ")"},
                            {DELIMITER, ")"},
                        });

    singleTest(" vari var \n \n  \t ivar val \n vall   ", {
                                                              {IDENTIFIER, "vari"},
                                                              {KEYWORD, "var"},
                                                              {IDENTIFIER, "ivar"},
                                                              {KEYWORD, "val"},
                                                              {IDENTIFIER, "vall"},
                                                          });
}

BOOST_AUTO_TEST_CASE(ARITHMETIC_OPERATORS) {
    singleTest("+7 + -4", {
                              {OPERATOR, "+"},
                              {INT_LITERAL, "7"},
                              {OPERATOR, "+"},
                              {OPERATOR, "-"},
                              {INT_LITERAL, "4"},
                          });

    singleTest("+28 + -0.47 + .8", {{OPERATOR, "+"},
                                    {INT_LITERAL, "28"},
                                    {OPERATOR, "+"},
                                    {OPERATOR, "-"},
                                    {FLOAT_LITERAL, "0.47"},
                                    {OPERATOR, "+"},
                                    {FLOAT_LITERAL, ".8"}});

    singleTest("+14+27-1 - -1+.3", {
                                       {OPERATOR, "+"},
                                       {INT_LITERAL, "14"},
                                       {OPERATOR, "+"},
                                       {INT_LITERAL, "27"},
                                       {OPERATOR, "-"},
                                       {INT_LITERAL, "1"},
                                       {OPERATOR, "-"},
                                       {OPERATOR, "-"},
                                       {INT_LITERAL, "1"},
                                       {OPERATOR, "+"},
                                       {FLOAT_LITERAL, ".3"},
                                   });

    singleTest("3 + + + - - 1", {
                                    {INT_LITERAL, "3"},
                                    {OPERATOR, "+"},
                                    {OPERATOR, "+"},
                                    {OPERATOR, "+"},
                                    {OPERATOR, "-"},
                                    {OPERATOR, "-"},
                                    {INT_LITERAL, "1"},
                                });
}

void testInvalidToken(const std::string& src) {
    BOOST_CHECK_THROW(Tokenizer(src).tokenize(), InvalidTokenException);
}

BOOST_AUTO_TEST_CASE(INVALID_TOKENS) { testInvalidToken("84.8.2"); }

}  // namespace cpmc
