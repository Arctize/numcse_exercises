#include <math.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

// 0.1
//
// a) 32 bits two's complement
//
// b)
// Taking an unsigned int makes it possible to
// print negative two's complement numbers aswell.
void int_to_bits(unsigned int x)
{
    if (x > 1)
	int_to_bits(x >> 1);
    printf("%i", x % 2);
}

void float_to_bits(float f)
{
    float* fPtr = &f;
    int* iPtr = (int*)fPtr;
    int i = *iPtr;
    int_to_bits(i);
}

// 0.2
// a)
double power(double a, int b)
{
    if (b < 0)
	return power(1 / a, -b);
    double result = a;
    for (int i = 0; i < b - 1; i++) {
	result *= a;
    }
    return result;
}

// b)
double fast_power(double a, int b)
{
    if (b == 1)
	return a;
    else if (b > 1)
	if (b % 2)
	    return a * fast_power(a, b - 1);
	else
	    return fast_power(a * a, b / 2);
    else if (b < 0)
	return fast_power(1 / a, -b);
    else
	return 1;
}

// c)
double faster_power(double a, int b)
{
    return exp(b * log(a));
}

// 0.3
// a)

// Starts overflowing at 13 (integers)
template <typename T>
T factorial(T n)
{
    T result = 1;
    while (n > 1)
	result *= n--;
    return result;
}

// b)
template <typename T>
double dbl_factorial(T n)
{
    return factorial(round(n));
}

int main(int argc, char* argv[])
{
    int_to_bits(11);
    printf("\n");

    int_to_bits(-10);
    printf("\n");

    float_to_bits(-2.5);
    printf("\n");

    printf("%f\n", power(2.5, 32));
    printf("%f\n", fast_power(2.5, 32));
    printf("%f\n", fast_power(10, -3));
    printf("%f\n", faster_power(2.5, 32));
    printf("%f\n", faster_power(10, -3));


    printf("%i\n", factorial(6));
    printf("%f\n", dbl_factorial(6.4));
    printf("%f\n", dbl_factorial(60));
    return 0;
}
