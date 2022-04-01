#include "Cli.hpp"
#include "CppCompiler.hpp"
#include "CppTranslator.hpp"
#include "Exception.hpp"
#include "IO.hpp"
#include "ProgramValidator.hpp"
#include "Tokenizer.hpp"
#include "ast/ProgramParser.hpp"

int main(int argc, const char** argv) {
    using namespace cpmc;

    // Parse CLI args
    CliArgResult args = CliArgParser().parse(argc, argv);

    // Read source code
    std::string sourceCode = readFileOrExit(args.sourceFileName);

    // Tokenize source code
    Tokenizer tokenizer(sourceCode);
    std::vector<Token> tokens;
    try {
        tokens = tokenizer.tokenize();
    } catch (const InvalidTokenException& e) {
        std::cout << e.getMessage() << std::endl;
        exit(0);
    }

    // Create parsing context
    ast::ParsingContext context(tokens);

    // Parse Program
    ast::ProgramParser parser(context);
    ast::Program program;
    try {
        program = parser.parse();
    } catch (const SyntaxError& e) {
        std::cout << e.getMessage() << std::endl;
        exit(0);
    }

    // Validate program
    ProgramValidator validator(program);
    ProgramValidatorResult validationResult = validator.validate();
    if (!validationResult.valid) {
        std::cout << "Invalid program." << std::endl;
        std::cout << validationResult.errorMessage << std::endl;
        exit(0);
    }

    // Translate CPM Program to C++ source code.
    CppTranslator transalator(program);
    CppSourceCode translated = transalator.translate();

    // Compile translated C++ source code.
    CppCompiler compiler;
    try {
        compiler.compile(translated, args.targetFileName);
    } catch (const CompilationException& e) {
        std::cout << e.getMessage() << std::endl;
        exit(0);
    }

    return 0;
}
