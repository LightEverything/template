#include <iostream>

const double pi = 3.14159;

double getcircleS(const double& r)
{
    return r * r * pi;
}

double getcircleC(const double& r)
{
    return 2 * r * pi;
}

int main(int argc, char** argv)
{
    double w, h;
    std::cin >> w >> h;
    double s = w * h, l = (w + h) * 2;
    std::cout << "S :" << s << ' ' << "L: " << l << '\n';

    double r;
    std::cin >> r;
    std::cout << "rs: "<< getcircleS(r) << "  "<< "rL: " << getcircleC(r) << '\n';
    return 0;
}