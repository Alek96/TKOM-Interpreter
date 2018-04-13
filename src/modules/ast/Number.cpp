#include "Number.hpp"

using namespace tkom::ast;

Number::Number(const int &value)
        : value(value) {
}

bool Number::operator==(const Number &rhs) const {
    return value == rhs.value;
}

bool Number::operator!=(const Number &rhs) const {
    return !(rhs == *this);
}

bool Number::operator<(const Number &rhs) const {
    return value < rhs.value;
}

bool Number::operator>(const Number &rhs) const {
    return rhs < *this;
}

bool Number::operator<=(const Number &rhs) const {
    return !(rhs < *this);
}

bool Number::operator>=(const Number &rhs) const {
    return !(*this < rhs);
}

const int &Number::getValue() const {
    return value;
}

void Number::setValue(int value) {
    Number::value = value;
}

