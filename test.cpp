#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#include <iostream>
#include <string>

std::string longDoubleToBinary(long double value)
{
    std::string binary = "";

    // Xác định biên
    long double epsilon = 0.0000000001;

    // Xét gần vô cùng vòng lặp để kiểm tra các giá trị nhị phân
    while (value > epsilon)
    {
        // Nhân giá trị với 2 và chia lấy phần dư để xác định bit tiếp theo
        value *= 2.0;
        if (value >= 1.0)
        {
            binary += "1";
            value -= 1.0;
        }
        else
        {
            binary += "0";
        }
    }

    return binary;
}

int main()
{
    long double value = 1234.56789;
    std::cout << longDoubleToBinary(value) << std::endl;
    return 0;
}
