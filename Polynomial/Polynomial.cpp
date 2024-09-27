#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

// 解析多項式字串
std::map<int, int> parsePolynomial(const std::string& input) {  //該函數接受一個 std::string 類型的參數 input，並返回一個 std::map<int, int> 類型的結果。
    std::map<int, int> polynomial;
    std::istringstream iss(input); //這個物件允許我們像讀取檔案一樣讀取字串。
    char ch;
    int coefficient, exponent;
    while (iss >> ch >> coefficient >> ch >> exponent) { //每次迴圈讀取一個字符 ch（用來跳過逗號和括號），一個係數 coefficient，再讀取一個字符 ch，然後讀取一個指數 exponent。這樣的讀取模式會一直持續到字串結束。
        polynomial[exponent] += coefficient;//•	將讀取到的係數 coefficient 加到 polynomial map 中對應的指數 exponent 上。如果該指數已經存在，則累加係數；如果不存在，則新增一個新的鍵值對。
    }
    return polynomial;
}

// 將多項式轉換為字串
std::string polynomialToString(const std::map<int, int>& polynomial) {
    std::string result;
    for (auto it = polynomial.rbegin(); it != polynomial.rend(); ++it) { //•	使用反向迭代器 rbegin() 和 rend() 來遍歷 polynomial map，從高次項到低次項
        if (it->second != 0) { //如果係數為零，則跳過該項。
            if (!result.empty() && it->second > 0) { //如果結果字串不為空，且係數大於零，則在結果字串前面加上加號。
                result += "+";
            }
            if (it->second < 0) {
                result += "-";
            }
            if (it->first == 0) { //如果指數為零，則只輸出係數。
                result += std::to_string(std::abs(it->second));
            }
            else if (it->first == 1) { //如果指數為一，則輸出係數和 x。
                result += std::to_string(std::abs(it->second)) + "x";
            }
            else { //否則輸出係數、x 和指數。
                result += std::to_string(std::abs(it->second)) + "x^" + std::to_string(it->first);
            }
        }
    }
    return result.empty() ? "0" : result; //如果結果字串為空，則返回 "0"；否則返回結果字串。
}

// 多項式相加
std::map<int, int> addPolynomials(const std::map<int, int>& p1, const std::map<int, int>& p2) {
    std::map<int, int> result = p1; //將 p1 複製到 result 中。
    for (const auto& term : p2) { //遍歷 p2 中的每一項。
        result[term.first] += term.second; //遍歷 p2 中的每一項，將其係數加到 result 中對應的指數上。
    }
    return result;
}

// 多項式相乘
std::map<int, int> multiplyPolynomials(const std::map<int, int>& p1, const std::map<int, int>& p2) {
    std::map<int, int> result;
    for (const auto& term1 : p1) { //遍歷 p1 中的每一項。
        for (const auto& term2 : p2) { //遍歷 p2 中的每一項。
            result[term1.first + term2.first] += term1.second * term2.second; //將兩個多項式的每一項相乘，然後將指數相加，係數相乘，加到 result 中。
        }
    }
    return result;
}

int main() {
    std::string input1, input2;

    std::cout << "請輸入第一個多項式 (格式: (係數, 指數, 係數, 指數, ...)): ";
    std::getline(std::cin, input1); //讀取一行輸入，存入 input1。

    std::cout << "請輸入第二個多項式 (格式: (係數, 指數, 係數, 指數, ...)): ";
    std::getline(std::cin, input2); //讀取一行輸入，存入 input2。

    auto poly1 = parsePolynomial(input1);
    auto poly2 = parsePolynomial(input2);

    std::cout << "Polynomial 1: " << polynomialToString(poly1) << std::endl;
    std::cout << "Polynomial 2: " << polynomialToString(poly2) << std::endl;

    auto sum = addPolynomials(poly1, poly2);
    auto product = multiplyPolynomials(poly1, poly2);

    std::cout << "Sum: " << polynomialToString(sum) << std::endl;
    std::cout << "Product: " << polynomialToString(product) << std::endl;

    return 0;
}

