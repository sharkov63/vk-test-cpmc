#define BOOST_TEST_MODULE CppCompiler_Test
#include "CppCompiler.hpp"

#include <boost/test/included/unit_test.hpp>
#include <cstdio>

#include "CppSourceCode.hpp"
#include "Exception.hpp"

namespace cpmc {

BOOST_AUTO_TEST_CASE(HelloWorld_Test) {
    const char* executable =
        "./HelloWorld_TestArtifact";  // in the same directory as the test executable
    const char* rawSource =
        "#include <iostream>                             \n"
        "int main() {                                    \n"
        "    std::cout << \"Hello World!\" << std::endl; \n"
        "    return 0;                                   \n"
        "}                                               \n";
    CppSourceCode source = std::string(rawSource);
    CppCompiler compiler("g++", "-x c++ - -o");

    BOOST_CHECK_NO_THROW(compiler.compile(source, executable));

    FILE* pipe = popen(executable, "r");
    BOOST_TEST(pipe != nullptr);

    char buf[32];
    BOOST_TEST(buf == fgets(buf, 32, pipe));
    BOOST_TEST(strcmp(buf, "Hello World!\n") == 0);
    BOOST_TEST(fgets(buf, 32, pipe) == nullptr);

    BOOST_TEST(pclose(pipe) == 0);
}

BOOST_AUTO_TEST_CASE(ExitCode_Test) {
    const char* executable = "./ExitCode_TestArtifact";
    const char* rawSource =
        "#include <iostream>                  \n"
        "int main() {                         \n"
        "    int x;                           \n"
        "    if (!(std::cin >> x)) return 2;  \n"
        "    if (x == 0) return 0;            \n"
        "    return 1;                        \n"
        "}                                    \n";

    CppSourceCode source = std::string(rawSource);
    CppCompiler compiler("g++", "-x c++ - -o");

    BOOST_CHECK_NO_THROW(compiler.compile(source, executable));

    // test for input "0"
    {
        FILE* pipe = popen(executable, "w");
        BOOST_TEST(pipe != nullptr);
        BOOST_TEST(fprintf(pipe, "%d\n", 0) >= 0);
        int exitStatus = WEXITSTATUS(pclose(pipe));
        BOOST_TEST(exitStatus == 0);
    }

    // test for input "1"
    {
        FILE* pipe = popen(executable, "w");
        BOOST_TEST(pipe != nullptr);
        BOOST_TEST(fprintf(pipe, "%d\n", 1) >= 0);
        int exitStatus = WEXITSTATUS(pclose(pipe));
        BOOST_TEST(exitStatus == 1);
    }

    // test for no input
    {
        FILE* pipe = popen(executable, "w");
        BOOST_TEST(pipe != nullptr);
        int exitStatus = WEXITSTATUS(pclose(pipe));
        BOOST_TEST(exitStatus == 2);
    }

    // test for invalid integer input
    {
        FILE* pipe = popen(executable, "w");
        BOOST_TEST(pipe != nullptr);
        BOOST_TEST(fprintf(pipe, "%s\n", "blah blah blah") >= 0);
        int exitStatus = WEXITSTATUS(pclose(pipe));
        BOOST_TEST(exitStatus == 2);
    }
}

BOOST_AUTO_TEST_CASE(CompilationError_Test) {
    const char* executable = "./CompilationError_TestArtifact";
    const char* rawSource =
        "#include <iostream>                            \n"
        "int main() {                                   \n"
        "     blah-blah-blah;                           \n"
        "}                                                ";
    CppSourceCode source = std::string(rawSource);
    CppCompiler compiler("g++", "-x c++ - -o");

    BOOST_CHECK_THROW(compiler.compile(source, executable), CompilationException);
}

}  // namespace cpmc
