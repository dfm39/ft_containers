# ft_containers

Welcome to the ft_containers project! In this project, we dive into the world of C++98 and reimagine essential container types inspired by the C++ Standard Template Library (STL). The goal is to implement various container types, adhering to the C++98 standard, while ensuring clean, readable, and well-structured code.

## Table of Contents
- [Chapter I Objectives](#chapter-i-objectives)
- [Chapter II General Rules](#chapter-ii-general-rules)
- [Compilation](#compilation)
- [Formatting and Naming Conventions](#formatting-and-naming-conventions)
- [Allowed/Forbidden](#allowedforbidden)
- [Design Requirements](#design-requirements)
- [Makefile](#makefile)
- [Read Me](#read-me)

## Chapter I Objectives

In this project, our main objective is to implement fundamental container types from the C++ Standard Template Library. We will follow the structure of each standard container as a reference, implementing only the parts necessary for their core functionality. All implementations must strictly adhere to the C++98 standard, incorporating even deprecated features.

## Chapter II General Rules

## Compilation

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

## Makefile

The provided Makefile offers convenient commands to compile and run tests. Customize your testing experience by using the appropriate make commands.

### Read Me

- You can organize your project files as needed while submitting mandatory files.
- Additional files are permitted for code organization.
- Exercise creativity, and remember that you cannot use STL containers to implement your own.

## By [dmf39]

Feel free to connect with me if you have any questions or suggestions!