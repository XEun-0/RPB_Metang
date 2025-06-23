#include "math_ops.h"
#include "string_ops.h" // cross-include

int square(int x) { return x * x; }

int cube(int x)
{
    return x * square(x); // test nested call
}

int factorial(int n)
{
    if (n <= 1) return 1;
    return n * factorial(n - 1); // recursion
}

int sum_array(const int* arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
        sum += arr[i];
    return sum;
}

void math_demo()
{
    int values[3] = {1, 2, 3};
    int total = sum_array(values, 3);
    print_result("Sum", total);           // from string_ops
    print_result("Square", square(4));
    print_result("Cube", cube(2));
}
