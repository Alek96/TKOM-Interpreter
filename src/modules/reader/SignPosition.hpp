#ifndef INTERPRETER_SIGNPOSITION_HPP
#define INTERPRETER_SIGNPOSITION_HPP

#include <ostream>

namespace tkom {

    struct SignPosition {
        SignPosition();
        SignPosition(const SignPosition& other) = default;

        bool operator==(const SignPosition &rhs) const;
        bool operator!=(const SignPosition &rhs) const;

        bool operator<(const SignPosition &rhs) const;
        bool operator>(const SignPosition &rhs) const;
        bool operator<=(const SignPosition &rhs) const;
        bool operator>=(const SignPosition &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const SignPosition &position);
        const std::string toString() const;

        unsigned int lineNumber;
        unsigned int signNumber;
        std::streampos linePosition;
        std::streampos signPosition;
    };

    inline std::ostream &operator<<(std::ostream &os, const SignPosition &position) {
        os << "lineNumber: " << position.lineNumber
           << ", signNumber: " << position.signNumber;
//           << ", linePosition: " << position.linePosition
//           << ", signPosition: " << position.signPosition;
        return os;
    }
}

#endif //INTERPRETER_SIGNPOSITION_HPP
