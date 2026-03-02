# AGENTS.md

## Cursor Cloud specific instructions

This is a C++ educational repository (CS 161A - Programming and Problem Solving I). There are no services, databases, or external dependencies.

### Build & Run

Compile any `.cpp` file with `g++`:
```
g++ -o <output> <source>.cpp
./<output>
```

The sample programs (`a1-sample.cpp`, `a2-sample.cpp`) require interactive stdin input. Pipe input when running non-interactively, e.g.:
```
echo "1000 5 2" | ./a1-sample
```

### Notes

- `main.cpp` is the student starter template; it prints "Hello, World!" by default.
- No build system (no Makefile/CMake), no package manager, no test framework. Compile directly with `g++`.
- Compiled binaries (`*.out`, `*.exe`, `*.o`, etc.) are gitignored — do not commit them.
