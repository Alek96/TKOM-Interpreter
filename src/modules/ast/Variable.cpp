#include "Variable.hpp"

using namespace tkom::ast;

Variable::Variable(std::vector<int> variables)
        : variables(std::move(variables)) {
}

Variable::Variable(Variable &&rhs) noexcept
        : variables(std::move(rhs.variables)) {
}

int &Variable::operator[](int idx) {
    return variables[idx];
}

const int &Variable::operator[](int idx) const {
    return variables[idx];
}

std::vector<int> &Variable::operator*() {
    return variables;
}

Variable Variable::operator==(const Variable &rhs) const {
    if (variables == rhs.variables) {
        return vTrue();
    } else {
        return vFalse();
    }
//    int i=0;
//    for (; i < variables.size() && i < rhs.variables.size(); ++i) {
//        if(variables[i] != rhs.variables[i])
//            return false;
//    }
//    if(variables.size() > rhs.variables.size()) {
//        for (; i < variables.size(); ++i) {
//            if(variables[i] != 0)
//                return false;
//        }
//    } else {
//        for (; i < rhs.variables.size(); ++i) {
//            if(rhs.variables[i] != 0)
//                return false;
//        }
//    }
//    return true;
}

Variable Variable::operator!=(const Variable &rhs) const {
    return !(rhs == *this);
}

Variable Variable::operator<(const Variable &rhs) const {
    if (variables < rhs.variables) {
        return vTrue();
    } else {
        return vFalse();
    }
}

Variable Variable::operator>(const Variable &rhs) const {
    return rhs < *this;
}

Variable Variable::operator<=(const Variable &rhs) const {
    return !(rhs < *this);
}

Variable Variable::operator>=(const Variable &rhs) const {
    return !(*this < rhs);
}

Variable Variable::operator+() const {
    return *this;
}

Variable Variable::operator-() const {
    Variable var(std::vector<int>(variables.size()));
    for (unsigned int i = 0; i < variables.size(); ++i) {
        var[i] = -variables[i];
    }
    return var;
}

Variable Variable::operator+(const Variable &rhs) const {
    Variable var;
    if (variables.size() == rhs.variables.size()) {
        var = *this;
        for (unsigned int i = 0; i < variables.size(); ++i) {
            var[i] += rhs.variables[i];
        }
    }

    return var;
}

Variable Variable::operator-(const Variable &rhs) const {
    Variable var;
    if (variables.size() == rhs.variables.size()) {
        var = *this;
        for (unsigned int i = 0; i < variables.size(); ++i) {
            var[i] -= rhs.variables[i];
        }
    }

    return var;
}

Variable Variable::operator*(const Variable &rhs) const {
    Variable var;
    if (variables.size() == rhs.variables.size()) {
        var = *this;
        for (unsigned int i = 0; i < variables.size(); ++i) {
            var[i] *= rhs.variables[i];
        }
    }

    return var;
}

Variable Variable::operator/(const Variable &rhs) const {
    Variable var;
    if (variables.size() == rhs.variables.size()) {
        var = *this;
        for (unsigned int i = 0; i < variables.size(); ++i) {
            var[i] /= rhs.variables[i];
        }
    }

    return var;
}

Variable Variable::operator%(const Variable &rhs) const {
    Variable var;
    if (variables.size() == rhs.variables.size()) {
        var = *this;
        for (unsigned int i = 0; i < variables.size(); ++i) {
            var[i] %= rhs.variables[i];
        }
    }

    return var;
}

Variable::operator bool() const {
    for (auto &&var : variables) {
        if (var)
            return true;
    }
    return false;
}

Variable Variable::operator!() const {
    if (*this) {
        return vFalse();
    } else {
        return vTrue();
    }
}

Variable Variable::operator&&(const Variable &rhs) const {
    if (static_cast<bool>(*this) && static_cast<bool>(rhs)) {
//        return Variable(std::vector<int>(1, 1));
        return vTrue();
    } else {
        return vFalse();
    }
}

Variable Variable::operator||(const Variable &rhs) const {
    if (static_cast<bool>(*this) || static_cast<bool>(rhs)) {
        return vTrue();
    } else {
        return vFalse();
    }
}

const Variable::Type Variable::getType() const {
    switch (variables.size()) {
        case 1:
            return Type::number;

        case 2:
            return Type::vector2;

        case 3:
            return Type::vector3;

        default:
            return Type::none;
    }
}

Variable Variable::vTrue() const {
    return Variable(std::vector<int>(1, 1));
}

Variable Variable::vFalse() const {
    return Variable(std::vector<int>(1, 0));
}
