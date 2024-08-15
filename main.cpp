#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string addition(std::string input) {
    std::stringstream ss(input);
    std::string I1, I2, base;

    ss >> I1 >> I2 >> base;

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

    // std::cout << "HERE" << std::endl;
    int newBase = std::stoi(base);
    // std::cout << "NOT HERE" << std::endl;
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

std::string subtraction(std::string input) {
    // std::cout << "WE GET HERE? " << input << std::endl;
    std::stringstream ss(input);
    std::string I1, I2, base;

    ss >> I1 >> I2 >> base;

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

    int newBase = std::stoi(base);

    std::vector<int> resultingSum;
    for (size_t i = 0; i < maxLength; i++) {
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

        int temp = digit1 - digit2 + carry;
        if (temp < 0) {
            temp = temp + newBase;
            carry = -1;
        } else {
            carry = 0;
        }

        resultingSum.insert(resultingSum.begin(), temp);
    }

    std::string result;
    for (size_t i = 0; i < resultingSum.size(); i++) {
        result = result + std::to_string(resultingSum[i]);
    }
    return result;
}

std::string karatsuba(std::string I1, std::string I2, std::string base) {
    if (I1.length() < 2 || I2.length() < 2) {
        return std::to_string(std::stoi(I1) * std::stoi(I2));
    } else {
        int k = std::ceil(std::min(I1.length(), I2.length()) / 2);

        std::string a1 = I1.substr(0, I1.length() - k);
        std::string a0 = I1.substr(I1.length() - k);
        std::string b1 = I2.substr(0, I2.length() - k);
        std::string b0 = I2.substr(I2.length() - k);

        std::string p0 = karatsuba(a0, b0, base);
        std::string p1 = karatsuba(a1, b1, base);

        std::string p2 = karatsuba(addition(a0 + " " + a1 + " " + base),
                                   addition(b0 + " " + b1 + " " + base), base);

        std::string p1Zero = "";
        for (int i = 0; i < 2 * k; i++) {
            p1Zero.push_back('0');
        }

        std::string p2Zero = "";
        for (int i = 0; i < k; i++) {
            p2Zero.push_back('0');
        }

        std::string subtractionResult1 =
            subtraction(p2 + " " + p1 + " " + base);
        std::string subtractionResult2 =
            subtraction(subtractionResult1 + " " + p0 + " " + base);

        std::string p1Return = p1 + p1Zero;
        std::string p2Return = subtractionResult2 + p2Zero;
        std::string p3Return = p0;

        std::string totalTemp1 = p1Return + " " + p2Return + " " + base;
        std::string temp1Add = addition(totalTemp1);

        std::string totalTemp2 = temp1Add + " " + p3Return + " " + base;
        std::string result = addition(totalTemp2);

        return result;
    }
}

std::string multiplication(std::string input) {
    std::stringstream ss(input);
    std::string I1, I2, base;

    ss >> I1 >> I2 >> base;

    std::string multiplicationAnswer = karatsuba(I1, I2, base);
    return multiplicationAnswer;
}

std::string division(std::string input) { return "0"; }

int main() {
    std::string input;
    std::getline(std::cin, input);

    std::cout << addition(input) << " ";
    std::cout << multiplication(input) << " ";
    std::cout << division(input) << std::endl;
}
