#include "Vector3.hpp"

using namespace tkom::ast;

Vector3::Vector3(const int &value1, const int &value2, const int &value3)
    : value({value1, value2, value3}) {}

bool Vector3::operator==(const Vector3 &rhs) const {
    return value == rhs.value;
}

bool Vector3::operator!=(const Vector3 &rhs) const {
    return !(rhs == *this);
}

bool Vector3::operator<(const Vector3 &rhs) const {
    return value < rhs.value;
}

bool Vector3::operator>(const Vector3 &rhs) const {
    return rhs < *this;
}

bool Vector3::operator<=(const Vector3 &rhs) const {
    return !(rhs < *this);
}

bool Vector3::operator>=(const Vector3 &rhs) const {
    return !(*this < rhs);
}

int &Vector3::operator[](std::size_t idx) {
    return value[idx];
}

const int &Vector3::operator[](std::size_t idx) const {
    return value[idx];
}

const Variable::Type Vector3::getType() const {
    return Type::vector3;
}

const std::vector<int> Vector3::getValue() const {
    return value;
}

const int &Vector3::getValue(const int &index) const {
    return value.at(index);
}

void Vector3::setValue(const std::vector<int> &value) {
    Vector3::value = value;
}