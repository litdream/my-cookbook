# Making a project, both sharable in C/C++

use `__cplusplus` and `extern "C" {}`

Usually, C project make "*.h" header file, but providing:

```c
extern "C" {
	...
	
}
```

This block provides 2 features for c++:

1. Don't Name-Mangle: Use the simpler C naming convention for the symbols, instead of the complex C++ name mangling needed for function overloading.

2. Use C Calling Convention: Use the C calling convention (how arguments are pushed onto the stack and how the function cleans up), which is typically simpler than C++ conventions.


## Make

gcc -c factorial_util.c
gcc main.c factorial_util.o
g++ main.cpp factorial_util.o
