cmake_minimum_required(VERSION 3.5)

# Project name
project(cpmc)

# Sources
set(CMAKE_SOURCE_DIR "src/")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

# Compilation
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "include/"
)


# Unit-testing

find_package(Boost REQUIRED)

# CppCompiler test
add_executable(CppCompiler_Test
    test/CppCompiler_Test.cpp
    src/CppCompiler.cpp
    src/CppSourceCode.cpp
    src/Token.cpp
    src/Exception.cpp)
target_include_directories(CppCompiler_Test PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(CppCompiler_Test PUBLIC "include/")
target_link_libraries(CppCompiler_Test PUBLIC ${Boost_LIBRARIES})

# Tokenizer test
add_executable(Tokenizer_Test
    test/Tokenizer_Test.cpp
    src/Tokenizer.cpp
    src/Token.cpp
    src/Exception.cpp)
target_include_directories(Tokenizer_Test PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(Tokenizer_Test PUBLIC "include/")
target_link_libraries(Tokenizer_Test PUBLIC ${Boost_LIBRARIES})

# ExpressionParser test
add_executable(ExpressionParser_Test
    test/ast/ExpressionParser_Test.cpp
    src/ast/ExpressionParser.cpp
    src/ast/Expression.cpp
    src/ast/ParsingContext.cpp
    src/Token.cpp
    src/Exception.cpp)
target_include_directories(ExpressionParser_Test PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(ExpressionParser_Test PUBLIC "include/")
target_link_libraries(ExpressionParser_Test PUBLIC ${Boost_LIBRARIES})

# InstructionParser test
add_executable(InstructionParser_Test
    test/ast/InstructionParser_Test.cpp
    src/ast/InstructionParser.cpp
    src/ast/InstructionComparator.cpp
    src/ast/InstructionDebugPrinter.cpp
    src/ast/Instruction.cpp
    src/ast/ExpressionParser.cpp
    src/ast/Expression.cpp
    src/ast/ParsingContext.cpp
    src/Token.cpp
    src/Exception.cpp)
target_include_directories(InstructionParser_Test PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(InstructionParser_Test PUBLIC "include/")
target_link_libraries(InstructionParser_Test PUBLIC ${Boost_LIBRARIES})

# ProgramParser test
add_executable(ProgramParser_Test
    test/ast/ProgramParser_Test.cpp
    src/ast/ProgramParser.cpp
    src/ast/Program.cpp
    src/ast/InstructionParser.cpp
    src/ast/InstructionComparator.cpp
    src/ast/InstructionDebugPrinter.cpp
    src/ast/Instruction.cpp
    src/ast/ExpressionParser.cpp
    src/ast/Expression.cpp
    src/ast/ParsingContext.cpp
    src/Token.cpp
    src/Exception.cpp)
target_include_directories(ProgramParser_Test PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(ProgramParser_Test PUBLIC "include/")
target_link_libraries(ProgramParser_Test PUBLIC ${Boost_LIBRARIES})
