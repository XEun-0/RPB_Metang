#include <iostream>
#include "string_ops.h"
#include "math_ops.h"

void print_result(const char* label, int value) {
    std::cout << label << ": " << value << std::endl;
}

void echo_input(const char* input)
{
    if (input) {
        std::cout << "Input: " << input << std::endl;
    }
}

void string_demo()
{
    echo_input("Hello from string_demo");
    print_result("Factorial(5)", factorial(5)); // call math_ops
}
