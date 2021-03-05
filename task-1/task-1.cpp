#include <iostream>
#include <cmath>

using namespace std;

int main()
{     
    double x = 1.825, y = 18.225, z = -3.298, a, b;

    a = pow(x, y / x) - pow(y / x, 1.0 / 3.0);
    b = (y - x) + ((y - z) / (y - x)) / (3 + pow(z, 2) / (5));

    cout << "x = " << x << "; y = " << y << "; z = " << z << ";\n";
    cout << "a = " << a << "\nb = " << b << endl;

    return 0;
}
