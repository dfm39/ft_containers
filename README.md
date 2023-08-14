# ft_containers

Welcome to school 42's ft_containers project! In this project, we dive into the world of C++98 and reimagine essential container types inspired by the C++ Standard Template Library (STL). The goal is to implement various container types, adhering to the C++98 standard, while ensuring clean, readable, and well-structured code.

## Table of Contents
- [Get Started](#get-started)
- [Subject](#subject)
- [Chapter I Objectives](#chapter-i-objectives)
- [Chapter II General Rules](#chapter-ii-general-rules)
- [Compilation](#compilation)
- [Formatting and Naming Conventions](#formatting-and-naming-conventions)
- [Allowed/Forbidden](#allowedforbidden)
- [Design Requirements](#design-requirements)
- [Additions](#additions)

## Get Started

To compile the project and run various tests, you can use the provided Makefile. Here are some useful commands:

- `make vector`: Compile and run tests for the vector container.
- `make stack`: Compile and run tests for the stack container.
- `make map`: Compile and run tests for the map container.
- `make set`: Compile and run tests for the set container.
- `make subject`: Compile and run additional tests from the 42 project page.

You can also use the following commands for more comprehensive tasks:

- `make all`: Compile and run all tests (vector, stack, map, set, and subject).
- `make clean`: Remove object files.
- `make fclean`: Remove compiled programs and test results.
- `make re`: Perform a clean rebuild of the project.

# Subject

## Chapter I Objectives

In this project, our main objective is to implement fundamental container types from the C++ Standard Template Library. We will follow the structure of each standard container as a reference, implementing only the parts necessary for their core functionality. All implementations must strictly adhere to the C++98 standard, incorporating even deprecated features.

## Chapter II General Rules

### Compilation

- Compile your code with `c++` using the flags `-Wall -Wextra -Werror`.
- The code should compile without errors when using the `-std=c++98` flag.
- Include a Makefile with essential rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.

### Formatting and Naming Conventions

- No strict coding style is enforced, but aim for clean and readable code.
- Properly name class files for each container type.

### Allowed/Forbidden

- Utilize C++ standard library features; avoid using external libraries, C++11 or later, and Boost libraries.
- Forbidden functions include `*printf()`, `*alloc()`, and `free()`. Usage will result in a grade of 0.

### Design Requirements

- Manage memory allocation to prevent memory leaks.
- Function implementations in header files (except for templates) will result in a grade of 0.
- Headers should be self-contained, avoiding double inclusion with proper include guards.

### Additions

- You can organize your project files as needed while submitting mandatory files.
- Additional files are permitted for code organization.
- Exercise creativity, and remember that you cannot use STL containers to implement your own.

### By dmf39 (alias dfranke)

Feel free to connect with me if you have any questions or suggestions!