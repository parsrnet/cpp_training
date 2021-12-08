#Day 2, Working with Types and Scope

## Assignment 1: Working with Types
For this assignment, please see [AssignTypeSizes](https://github.com/parsrnet/cpp_training/tree/main/Week1/Day2/AssignTypeSizes) for my source code and explanations in source code annotations

## Assignment 2: C++ Type Ideosyncracies
One of the major limitations of my program is that all the types have to be baked into the map and we have no feature to search through all standard types at runtime. I don't necessarily see this as a limitation, so much as a requirement for C programs to be quite explicit to avoid unintentional behaviors; however, compared to C# and Java, there's not much of a sense of reflection unless you explicitly include it in the program which can oftentimes make the source-code unwieldy. You'll see that the user has no interaction with the system itself, but instead sends commands which are searched through a map. In C#, we could actually allow the user to interact with and query all the types exposed during Runtime using "Type.GetType(string)", which would make this program leagues shorter - but at the cost of removing a lot of the explicit characteristics of C and C++ that allow us to finely manage our memory, for instance.

## Assignment 3: C++ Debugging
It's important to note that LLDB is a fantastic debugging tool for use with clang! As for command line options, we use the '-g' flag to tell the compiler to add debug information to the output file. From there, we use `lldb [program]` to launch the debugger, `b` to add breakpoints, and `run` to launch the program in debug mode.

## Assignment 4: C++ Compiler Options
We use the `-c` flag with clang++ to generate only an object file.

## Assignment 5: Float Precision
For this assignment, please see [AssignFloatPrecision](https://github.com/parsrnet/cpp_training/tree/main/Week1/Day2/AssignFloatPrecision) for source code and explanations in code annotations.
