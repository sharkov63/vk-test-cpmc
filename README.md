# CPMC (C+\- Compiler)

This is a compiler of a fictional C+\- language. It translates C+\- source code into C++ source code and then compiles it using other C++ compiler. This is a solution of the test task in VK internship selection for KPHP team.

## C+\- language

This is a fictional language which consists of variables, constants, literals (string and numeric), functions `print` and `input`.

This language is dynamically typed: variables can store values of different types. There are three primitive types:
* Int
* String
* Float

Also, there are arithmetic operators `+` and `-` and assignment operator `=`.

All types can be on either side of arithmetic operators. The operation rules are as follows (the order of arguments does not matter here):
* String + Int/Float --- the number is converted to string, and then two strings are concatenated.
* String - Int/Float --- the string is converted to an integer or float, and then two numbers are subtracted. If the string cannot be converted to a number, it is treated as a zero.
* Float +- Int --- the integer is converted to a float.

An example of C+\- code (can be found at `samples/sample.cpm`):
```
var str = "Hello"; // variable is declared by var
str = str + "!";   // variables can be modified
print(str);        // function print accepts one parameter

str = 21 + 2 + 18; // you can assign an int to the same variable
print(str);        // -> 41

val worldString = "World"; // a constant is created by val keyword
val answerNumber = 42;

print(worldString + answerNumber); // -> World42
print(worldString - answerNumber); // -> -42

val pi = 3.14;
print(pi + answerNumber); // -> 45.14

val numberString = "134";
print(numberString - answerNumber); // -> 92
print(numberString + answerNumber); // -> 13442

val name = input("Name: ");      // prints "Name: " and waits for input
print("Your name is: " + name);
```

## Dependencies

* For `cpmc` to work it is required to have `g++` in path. Currently, there is no way to select other C++ compiler.

* `cmake` and `make` for building

* Boost for building and running unit-tests.

## Building

At the root of the cloned repository on your machine, run `cmake` and then `make` (in your build directory):

```sh
cmake -S./ -Bbuild/
cd build/
make cpmc
```

## Usage
```sh
cpmc <SOURCE_FILE> <TARGET_FILE>
```


## Testing

There are several unit-tests as targets in `CMakeLists.txt`. You can build any of them by `make <TARGET_NAME>`, and then run the built executable.
