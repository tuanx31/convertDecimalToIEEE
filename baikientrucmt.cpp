#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class Standard
{
public:
    int bias;
    int bitS = 1;
    int bitE;
    int bitM;
    Standard()
    {
    }

    Standard(int bias, int bitE, int bitM)
    {
        this->bias = bias;
        this->bitE = bitE;
        this->bitM = bitM;
    }
};

Standard s32bit(127, 8, 23);
Standard s80bit(16383, 15, 64);

class IEEE
{
    Standard typeIEEE;

public:
    IEEE(Standard type)
    {
        this->typeIEEE = type;
    }
    int find_b(string number)
    {
        int dotPosition = number.find('.');
        int onePos = -1;
        for (int i = 0; i < number.length(); i++)
        {
            if (number[i] == '1')
            {
                onePos = i;
                break;
            }
        }

        int numOfBits = 0;

        if (dotPosition > onePos)
        {
            numOfBits = dotPosition - onePos - 1;
        }
        else
        {
            numOfBits = (onePos - dotPosition) * -1;
        }

        return numOfBits;
    }

    // Chuyển đổi phần nguyên sang nhị phân
    string intToBinary(int n)
    {
        if (n == 0)
            return "0";

        string result = "";
        while (n > 0)
        {
            result = ((n % 2) == 0 ? "0" : "1") + result;
            n /= 2;
        }
        return result;
    }

    // Chuyển đổi phần thập phân sang nhị phân
    string fractionalToBinary(double num)
    {
        if (num >= 1 || num <= 0)
            return "";

        string result = "";
        while (num > 0)
        {
            // Nhân số thực với 2 để xem bit tiếp theo là 0 hay 1
            double temp = num * 2;
            if (temp >= 1)
            {
                result += "1";
                num = temp - 1;
            }
            else
            {
                result += "0";
                num = temp;
            }
        }
        return result;
    }

    // Hàm chuyển đổi số thực sang nhị phân
    string floatToBinary(double num)
    {
        // Xác định dấu của số và chuyển đổi thành số dương
        string sign = (num < 0) ? "1" : "0";
        num = abs(num);

        int intPart = (int)num;
        double fractionalPart = num - intPart;

        string intBinary = intToBinary(intPart);
        string fractionalBinary = fractionalToBinary(fractionalPart);

        return intBinary + "." + fractionalBinary;
    }
    /// @brief Tìm S trong bộ S E M
    /// @param num tham số đầu vào
    /// @return S
    string findS(double num)
    {
        return num < 0 ? "1" : "0";
    }

    string findE(double num)
    {
        int E = typeIEEE.bias + find_b(floatToBinary(num));
        string Ebin = floatToBinary(E);
        Ebin.pop_back();
        while (Ebin.length() < typeIEEE.bitE)
        {
            Ebin.insert(0, 1, '0');
        }
        return Ebin;
    }

    string findM(double num)
    {
        string result;

        string bin = floatToBinary(num);

        int dotPosition = bin.find('.');
        int b = find_b(bin);
        if (b > 0)
        {
            bin.erase(dotPosition, 1);
            result = bin.substr(dotPosition - b);
        }
        else
        {
            // cout << "vi tri :" << dotPosition - b << endl;
            result = bin.substr(dotPosition - b + 1);
        }
        while (result.length() < typeIEEE.bitM)
        {
            result.push_back('0');
        }
        return result;
    }

    string finalResultBin(double number)
    {
        string res = findS(number) + findE(number) + findM(number);
        return res;
    }

    char get_hex_char(std::string four_bit_str)
    {
        int value = 8 * (four_bit_str[0] - '0') + 4 * (four_bit_str[1] - '0') + 2 * (four_bit_str[2] - '0') + (four_bit_str[3] - '0');

        if (value <= 9)
            return '0' + value;
        else
            return 'A' + value - 10;
    }

    string finalResultHex(string chuoiBin)
    {
        string hexa = "";

        for (int i = 0; i < chuoiBin.size(); i += 4)
        {
            hexa += get_hex_char(chuoiBin.substr(i, 4));
        }
        return hexa;
    }
};

void inketQua(IEEE iee, double num)
{
    string binary = iee.floatToBinary(num);
    string sign = iee.findS(num) == "0" ? "" : "-";
    cout << "Bin :" << sign << binary << endl;
    cout << "số mũ cần nhân để định chuẩn : " << iee.find_b(binary) << endl;
    cout << "S :" << iee.findS(num) << endl;
    cout << "E :" << iee.findE(num) << endl;
    cout << "M :" << iee.findM(num) << endl;
    cout << "\nSEM :";
    string resultBin = iee.finalResultBin(num);
    int space = 1;
    for (auto item : resultBin)
    {
        cout << item;
        if (space % 4 == 0)
        {
            cout << " ";
        }
        space++;
    }
    string hex = iee.finalResultHex(resultBin);
    cout << "\nHex :";
    int h = 1;
    for (auto item : hex)
    {
        cout << item;
        if (h % 2 == 0)
        {
            cout << " ";
        }
        h++;
    }
    cout << " H";
}

bool kiemTraDinhDang(string input)
{
    stringstream ss(input);
    int tuSo, mauSo;
    char delimiter;
    // Kiểm tra xem có thể đọc tử số và mẫu số từ chuỗi không
    if (!(ss >> tuSo >> delimiter >> mauSo))
    {
        return false;
    }
    // Kiểm tra dấu '/' sau tử số và trước mẫu số
    if (delimiter != '/')
    {
        return false;
    }
    // Kiểm tra mẫu số khác 0
    if (mauSo == 0)
    {
        return false;
    }
    return true;
}

class PhanSo
{
public:
    double tuSo, mauSo;

    void in()
    {
        cout << tuSo << "/" << mauSo;
    }

    void nhap()
    {
        string chuoi;
        do
        {
            cout << "Nhập vào phân số (ví dụ 19/64) :";
            cin >> chuoi;
            if (!kiemTraDinhDang(chuoi))
            {
                cout << "Chuỗi nhập vào không hợp lệ , vui lòng nhập lại \n";
            }

        } while (!kiemTraDinhDang(chuoi));

        int pos = chuoi.find('/');
        string tuSoStr = chuoi.substr(0, pos);
        string mauSoStr = chuoi.substr(pos + 1);

        tuSo = stod(tuSoStr);   // Chuyển từ chuỗi sang double
        mauSo = stod(mauSoStr); // Chuyển từ chuỗi sang double
    }
};

int main()
{
    PhanSo ps;
    ps.nhap();
    IEEE iee(s32bit);
    cout << endl
         << "====================KQ====================" << endl;
    inketQua(iee, ps.tuSo / ps.mauSo);
}
