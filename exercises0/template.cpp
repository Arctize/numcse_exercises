#include <iostream>

template <class T>
T squared_norm(T x, T y)
{
    return x * x + y * y;
}

template <typename T>
class Point {
    T x, y;

public:
    Point(T _x, T _y)
    {
	x = _x;
	y = _y;
    }

    T rad()
    {
	return squared_norm(x, y);
    }
};

int main(int argc, char* argv[])
{
    std::cout << squared_norm(3, 4) << std::endl;
    Point<int> p(5, 5);
    std::cout << p.rad() << std::endl;

    return 0;
}
