// c_main.c

#include <stdio.h>
#include "factorial_util.h"

int main() {
    int num = 5;
    unsigned long long result = calculate_factorial(num);
    printf("C Project: Factorial of %d is %llu\n", num, result);
    return 0;
}
