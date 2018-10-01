#include <stdio.h>
#include <math.h>

// 0.1
//
// a) 32 bits two's complement
//
// b)
void int_to_bits(int x)
{
    if (x > 1)
	int_to_bits(x >> 1);
    printf("%i", x % 2);
}

// 0.2
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
template <typename T>
T factorial(T n)
{
    T result = 1;
    while (n > 1)
	result *= n--;
    return result;
}

// b)
double dbl_factorial(double d)
{
    return factorial(round(d));
}

int main(int argc, char* argv[])
{
    int_to_bits(11);
    printf("\n");

    printf("%f\n", fast_power(2.5, 32));
    printf("%f\n", faster_power(2.5, 32));

    printf("%i\n", factorial(6));
    printf("%f\n", dbl_factorial(6.4));
    return 0;
}
