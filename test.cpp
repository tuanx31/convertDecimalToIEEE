#include <iostream>
#include <bitset>
using namespace std;
int main()
{
    float f = 0.05;
    int f_int = *reinterpret_cast<int *>(&f);
    std::bitset<32> f_bits(f_int);

    std::cout << f_bits;
    return 0;
}