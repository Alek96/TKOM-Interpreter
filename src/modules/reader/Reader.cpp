#include "Reader.hpp"

#include <utility>

#include "exception/Exception.hpp"

using namespace tkom;

Reader::Reader(std::istream &istream_)
        : istream(istream_) {
    position.linePosition = istream.tellg();
    position.signPosition = istream.tellg();
}

/*Reader::Reader(std::string &filePath) {
    fileHandler = std::make_unique<std::fstream>(filePath);
    if (fileHandler->fail()) {
        //Error
        std::string message = std::string("Fail to open files: ").append(filePath);

        Printer::instance().error(message);
        throw Exception(message);
    }
    istream = &*fileHandler;
    position.linePosition = this->istream->tellg();
    position.signPosition = this->istream->tellg();
}*/

const char Reader::get() {
    istream.get(sign);

    if (sign == '\n' || sign == '\r') {
        if (previousSign != sign &&
            (previousSign == '\n' || previousSign == '\r')) {
            // CRLF or LFCR, just skip it
        } else {
            position.lineNumber++;
            position.signNumber = 0;
            position.linePosition = istream.tellg();
        }
    } else {
        position.signNumber++;
    }
    previousSign = sign;
    position.signPosition = istream.tellg();

    return sign;
}

const char Reader::peek() {
    return static_cast<char>(istream.peek());
}

const SignPosition &Reader::getPosition() const {
    return position;
}

const bool Reader::eof() const {
    return istream.eof();
}
