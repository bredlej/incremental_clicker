#ifndef BIGNUM_HPP
#define BIGNUM_HPP

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>

struct BigNumberValue {
    double value;
    int exp;
};
class BigNumber {
    double value;
    int exp;
    bool negative;

    static const int MAX_MAGNITUDE = 12;
    static const double TEN_CUBED;
    static const std::unordered_map<int, std::string> powTenToName;
    static const std::unordered_map<int, std::string> powTenToAffix;

public:
    constexpr BigNumber() {
        this->value = 0;
        this->exp = 0;
        this->negative = false;
    }
    constexpr BigNumber(double value, int exp = 0) : value(value), exp(exp), negative(false) {
        if (value < 0) {
            throw std::invalid_argument("Negative numbers are not supported.");
        }
        normalize();
    }

    BigNumberValue persistence() const {
        return {value, exp};
    }

    constexpr BigNumber(BigNumber const &other) {
        this->value = other.value;
        this->exp = other.exp;
        this->negative = other.negative;
    }

    constexpr void normalize() {
        if (value < 1 && exp != 0) {
            value *= TEN_CUBED;
            exp -= 3;
        } else if (value >= TEN_CUBED) {
            while (value >= TEN_CUBED) {
                value /= TEN_CUBED;
                exp += 3;
            }
        } else if (value <= 0) {
            negative = value < 0;
            exp = 0;
            value = 0;
        }
    }

    constexpr void align(int exp) {
        int d = exp - this->exp;
        if (d > 0) {
            value = (d <= MAX_MAGNITUDE) ? value / std::pow(10, d) : 0;
            this->exp = exp;
        }
    }

    constexpr BigNumber add(const BigNumber& bigNum) const {
        BigNumber result = *this;
        if (bigNum.exp < result.exp) {
            BigNumber temp = bigNum;
            temp.align(result.exp);
            result.value += temp.value;
        } else {
            result.align(bigNum.exp);
            result.value += bigNum.value;
        }
        result.normalize();
        return result;
    }

    constexpr BigNumber subtract(const BigNumber& bigNum) const {
        BigNumber result = *this;
        if (bigNum.exp < result.exp) {
            BigNumber temp = bigNum;
            temp.align(result.exp);
            result.value -= temp.value;
        } else {
            result.align(bigNum.exp);
            result.value -= bigNum.value;
        }
        result.normalize();
        return result;
    }

    constexpr BigNumber multiply(double factor) const {
        BigNumber result = *this;
        if (factor >= 0) {
            result.value *= factor;
            result.normalize();
        }
        return result;
    }

    constexpr BigNumber divide(double divisor) const {
        BigNumber result = *this;
        if (divisor > 0) {
            result.value /= divisor;
            result.normalize();
        }
        return result;
    }

    constexpr int compare(const BigNumber& bigNum) const {
        BigNumber a = *this;
        BigNumber b = bigNum;
        a.align(b.exp);
        b.align(a.exp);
        if (a.value < b.value) return -1;
        if (a.value > b.value) return 1;
        return 0;
    }

    std::string getValue(int precision = 3) const {
        return std::to_string(static_cast<int>(value * std::pow(10, precision)) / std::pow(10, precision));
    }

    std::string getExpName() const {
        return powTenToAffix.at(exp);
    }

    std::string getExp() const {
        return std::to_string(exp);
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << value << " " << getExpName();
        return oss.str();
    }
};

#endif // BIGNUM_HPP