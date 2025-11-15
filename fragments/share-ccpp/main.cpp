// cpp_main.cpp

#include <iostream>
// Include the C header file
#include "factorial_util.h"

int main() {
    int num = 7;
    // Call the C function directly!
    unsigned long long result = calculate_factorial(num);
    
    std::cout << "C++ Project: Factorial of " << num 
              << " is " << result << std::endl;
              
    return 0;
}
