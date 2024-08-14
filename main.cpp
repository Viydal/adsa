#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string addition(std::string input) {
    std::stringstream ss(input);
    std::string I1, I2, base;

    ss >> I1 >> I2 >> base;

    std::cout << I1 << " " << I2 << " " << base << std::endl;

    std::vector<int> firstNum(I1.length(), 0);
    std::vector<int> secondNum(I2.length(), 0);

    for (size_t i = 0; i < I1.length(); i++) {
        firstNum[i] = I1[i] - '0';
    }

    for (size_t i = 0; i < I2.length(); i++) {
        secondNum[i] = I2[i] - '0';
    }

    size_t maxLength = std::max(firstNum.size(), secondNum.size());

    int carry = 0;
    int sum = 0;

    int newBase = std::stoi(base);

    std::vector<int> resultingSum;
    for (size_t i = 0; i < maxLength; i++) {
        sum = 0;

        int digit1;
        if (i < firstNum.size()) {
            digit1 = firstNum[firstNum.size() - 1 - i];
        } else {
            digit1 = 0;
        }

        int digit2;
        if (i < secondNum.size()) {
            digit2 = secondNum[secondNum.size() - 1 - i];
        } else {
            digit2 = 0;
        }

        sum = digit1 + digit2 + carry;

        carry = floor(sum / newBase);

        sum = sum % newBase;

        resultingSum.insert(resultingSum.begin(), sum);
    }

    if (carry > 0) {
        resultingSum.insert(resultingSum.begin(), carry);
    }

    std::string result;
    for (size_t i = 0; i < resultingSum.size(); i++) {
        result = result + std::to_string(resultingSum[i]);
    }

    return result;
}

std::string karatsuba(std::string I1, std::string I2, std::string base) {
    if (I1.length() < 2 || I2.length() < 2) {
        std::cout << std::stoi(I1) << " TIMES " << std::stoi(I2) << " = "
                  << std::to_string(std::stoi(I1) * std::stoi(I2)) << std::endl;
        return std::to_string(std::stoi(I1) * std::stoi(I2));
    } else {
        int k = std::ceil(std::min(I1.length(), I2.length()) / 2);

        std::string a1 = I1.substr(0, I1.length() - k);
        std::string a0 = I1.substr(I1.length() - k);
        std::string b1 = I2.substr(0, I2.length() - k);
        std::string b0 = I2.substr(I2.length() - k);

        std::string p0 = karatsuba(a0, b0, base);
        std::string p1 = karatsuba(a1, b1, base);
        std::string p2 =
            karatsuba(std::to_string(std::stoi(a0) + std::stoi(a1)),
                      std::to_string(std::stoi(b0) + std::stoi(b1)), base);

        std::string p1Zero = "";
        for (int i = 0; i < 2 * k; i++) {
            p1Zero.push_back('0');
        }

        std::string p2Zero = "";
        for (int i = 0; i < k; i++) {
            p2Zero.push_back('0');
        }

        std::string p1Return = p1 + p1Zero;
        std::string p2Return =
            std::to_string(std::stoi(p2) - std::stoi(p1) - std::stoi(p0)) +
            p2Zero;
        std::string p3Return = p0;

        std::string total = std::to_string(std::stoi(p1Return) + std::stoi(p2Return) + std::stoi(p3Return));

        int temp = std::stoi(total);
        total = std::to_string(temp);
        return total;
    }
}

std::string multiplication(std::string input) {
    std::stringstream ss(input);
    std::string I1, I2, base;

    ss >> I1 >> I2 >> base;

    std::string multiplicationAnswer = karatsuba(I1, I2, base);
    return multiplicationAnswer;
}

int main() {
    std::string input1 = "123 132 10";
    std::string input2 = "101 1111 2";

    std::cout << addition(input1) << std::endl;
    std::cout << multiplication(input1) << std::endl;
    std::cout << std::endl;
    std::cout << addition(input2) << std::endl;
    std::cout << multiplication(input2) << std::endl;
}
