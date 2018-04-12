#ifndef INTERPRETER_FILEREADER_HPP
#define INTERPRETER_FILEREADER_HPP

#include <istream>
#include <memory>

#include "SignPosition.hpp"

namespace tkom {

    class Reader {
    public:
        explicit Reader(std::istream &istream);

        Reader(const Reader &) = delete;
        const Reader &operator=(const Reader &) = delete;

        const char get();
        const char peek();
        const SignPosition &getPosition() const;
        const bool eof() const;

    private:
        std::istream &istream;
        char sign = 0;
        char previousSign = 0;
        SignPosition position;
    };
}

#endif //INTERPRETER_FILEREADER_HPP
