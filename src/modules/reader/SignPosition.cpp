#include "SignPosition.hpp"

using namespace tkom;

SignPosition::SignPosition()
        : lineNumber(1),
          signNumber(0),
          linePosition(linePosition),
          signPosition(signPosition) {}

bool SignPosition::operator==(const SignPosition &rhs) const {
    return lineNumber == rhs.lineNumber &&
           signNumber == rhs.signNumber &&
           linePosition == rhs.linePosition &&
           signPosition == rhs.signPosition;
}

bool SignPosition::operator!=(const SignPosition &rhs) const {
    return !(rhs == *this);
}

bool SignPosition::operator<(const SignPosition &rhs) const {
    if (lineNumber < rhs.lineNumber)
        return true;
    if (rhs.lineNumber < lineNumber)
        return false;
    return signNumber < rhs.signNumber;
}

bool SignPosition::operator>(const SignPosition &rhs) const {
    return rhs < *this;
}

bool SignPosition::operator<=(const SignPosition &rhs) const {
    return !(rhs < *this);
}

bool SignPosition::operator>=(const SignPosition &rhs) const {
    return !(*this < rhs);
}

