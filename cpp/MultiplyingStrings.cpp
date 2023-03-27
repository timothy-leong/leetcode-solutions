#include <algorithm>
#include <functional>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    /// @brief We reproduce primary school algorithms.
    /// @param num1 The first number
    /// @param num2 The second number
    /// @return The product
    string multiply(string num1, string num2)
    {
        // Edge case: One of the numbers is 0.
        if (num1 == "0" || num2 == "0")
        {
            return "0";
        }

        // Reverse both strings (we want "big-endian"-ness)
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        string result;
        for (int i{}; i < num2.size(); ++i)
        {
            auto nextProduct{multiplyByOneDigit(num1, num2[i], i)};
            result = add(result, nextProduct);
        }

        reverse(result.begin(), result.end());
        return result;
    }

    string multiplyByOneDigit(string &num, char digit, int numZeros)
    {
        const int mult_digit{digit - '0'};
        string result(numZeros, '0');
        result.reserve(num.length());

        function<void(const int, const int)> multiply;
        multiply = [&](const int index, const int carry)
        {
            if (index == num.length())
            {
                if (carry > 0)
                {
                    result.push_back('0' + carry);
                }
                return;
            }

            const int product{(num[index] - '0') * mult_digit + carry};
            result.push_back('0' + (product % 10));
            multiply(index + 1, product / 10);
        };

        multiply(0, 0);
        return result;
    }

    string add(string &s1, string &s2)
    {
        string result;
        result.reserve(max(s1.length(), s2.length()));

        function<void(const int, const int, const int)> sum;
        sum = [&](const int i, const int j, const int carry)
        {
            if (i >= s1.length() && j >= s2.length() && carry == 0)
            {
                return;
            }

            const int s1_digit = i < s1.length() ? s1[i] - '0' : 0;
            const int s2_digit = j < s2.length() ? s2[j] - '0' : 0;
            const int digit_sum = s1_digit + s2_digit + carry;

            result.push_back('0' + (digit_sum % 10));
            sum(i + 1, j + 1, digit_sum > 9 ? 1 : 0);
        };

        sum(0, 0, 0);
        return result;
    }
};