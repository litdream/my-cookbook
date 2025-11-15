// factorial_util.h

#ifndef FACTORIAL_UTIL_H
#define FACTORIAL_UTIL_H

// This block is the magic for C++ compatibility!
// It tells the C++ compiler (when __cplusplus is defined)
// to treat the enclosed function declarations as C functions,
// which prevents C++ name mangling.
#ifdef __cplusplus
extern "C" {
#endif

// --- Utility Function Declaration ---
/**
 * Calculates the factorial of a non-negative integer.
 * @param n The number to calculate the factorial of.
 * @return The factorial result (unsigned long long).
 */
unsigned long long calculate_factorial(int n);


#ifdef __cplusplus
} // end extern "C"
#endif

#endif // FACTORIAL_UTIL_H
