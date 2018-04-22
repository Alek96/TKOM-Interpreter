#include "Variable.hpp"
#include "exception/Exception.hpp"

#include <string>
#include <sstream>

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
                            + std::to_string(rhs.variables.size()) + "-dimension vector "
                            + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
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
        throw MathException("Can't subtract "
                            + std::to_string(variables.size()) + "-dimension vector and "
                            + std::to_string(rhs.variables.size()) + "-dimension vector "
                            + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
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
                            + std::to_string(rhs.variables.size()) + "-dimension vector "
                            + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
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
                            + std::to_string(variables.size()) + "-dimension vector by "
                            + std::to_string(rhs.variables.size()) + "-dimension vector "
                            + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
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
                            + std::to_string(variables.size()) + "-dimension vector by "
                            + std::to_string(rhs.variables.size()) + "-dimension vector "
                            + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
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

const unsigned int Variable::size() const {
    return variables.size();
}

const tkom::SignPosition &Variable::getPosition() const {
    return sPos;
}

void Variable::setPosition(const tkom::SignPosition &sPos) {
    Variable::sPos = sPos;
}

int &Variable::at(unsigned idx) {
    if (0 <= idx && idx < variables.size()) {
        return variables.at(idx);
    } else {
        throw MathException("index out of range of n-dimension vector's "
                            + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
    }
}

const int &Variable::at(unsigned idx) const {
    if (0 <= idx && idx < variables.size()) {
        return variables.at(idx);
    } else {
        throw MathException("index out of range of n-dimension vector's "
                            + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
    }
}

const std::string Variable::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}
