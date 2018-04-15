#include "Variable.hpp"
#include "exception/Exception.hpp"

#include <string>

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
    } else {
        throw MathException("Can't add "
                            + std::to_string(variables.size()) + "-dimension vector and "
                            + std::to_string(rhs.variables.size()) + "-dimension vector at line: ...");
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
    } else {
        throw MathException("Can't compare "
                            + std::to_string(variables.size()) + "-dimension vector and "
                            + std::to_string(rhs.variables.size()) + "-dimension vector at line: ...");
    }

    return var;
}

Variable Variable::operator*(const Variable &rhs) const {
    Variable var;
    if (variables.size() == 1) {
        var = rhs;
        for (auto &variable : var.variables) {
            variable *= variables[0];
        }
    } else if (rhs.variables.size() == 1) {
        var = *this;
        for (auto &variable : var.variables) {
            variable *= rhs.variables[0];
        }
    } else {
        throw MathException("Can't multiply "
                            + std::to_string(variables.size()) + "-dimension vector and "
                            + std::to_string(rhs.variables.size()) + "-dimension vector at line: ...");
    }

    return var;
}

Variable Variable::operator/(const Variable &rhs) const {
    Variable var;
    if (rhs.variables.size() == 1) {
        var = *this;
        for (auto &variable : var.variables) {
            variable /= rhs.variables[0];
        }
    } else {
        throw MathException("Can't divide "
                            + std::to_string(variables.size()) + "-dimension vector and "
                            + std::to_string(rhs.variables.size()) + "-dimension vector at line: ...");
    }

    return var;
}

Variable Variable::operator%(const Variable &rhs) const {
    Variable var;
    if (rhs.variables.size() == 1) {
        var = *this;
        for (auto &variable : var.variables) {
            variable %= rhs.variables[0];
        }
    } else {
        throw MathException("Can't modulo "
                            + std::to_string(variables.size()) + "-dimension vector and "
                            + std::to_string(rhs.variables.size()) + "-dimension vector at line: ...");
    }

    return var;
}

Variable::operator bool() const {
    return !variables.empty();
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

Variable Variable::vTrue() const {
    return Variable(std::vector<int>(1, 1));
}

Variable Variable::vFalse() const {
    return Variable();
}
