## Cursor Cloud specific instructions

This is a C++ course repository (CS 161A - Programming and Problem Solving I). There are no package managers, build systems, services, or databases.

**Compiling:** Use `g++ -Wall -Wextra -std=c++17 -o <output> <source>.cpp` to compile any `.cpp` file. The compiler (`g++ 13.3`) is pre-installed.

**Running:** Programs are standalone executables. Some require interactive `cin` input; pipe input via `echo -e "val1\nval2" | ./<program>` for non-interactive execution.

**No lint/test/build tooling:** There is no Makefile, CMake, test framework, or linter configured. Compilation with `-Wall -Wextra` serves as the lint check.
