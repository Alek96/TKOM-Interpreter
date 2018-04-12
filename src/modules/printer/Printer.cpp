#include "Printer.hpp"

#include <sstream>

#include "modules/printer/console_colour/ConsoleColour.h"

using namespace tkom;

Printer::Printer()
        : output(&std::cout), errorOutput(nullptr), shiftMultiplier(2), labelShift(1) {}

void Printer::error(const std::string &message, const unsigned int &labelShift) {
    if (enableOutput && (output || errorOutput)) {
        (errorOutput ? *errorOutput : *output) << Colour(Colour::Error)
                                               << printToString(addLabel("Error"), labelShift)
                                               << Colour(Colour::None)
                                               << printToString(message, labelShift + this->labelShift);
    }
}

void Printer::warning(const std::string &message, const unsigned int &labelShift) {
    if (enableOutput && (output || errorOutput)) {
        (errorOutput ? *errorOutput : *output) << Colour(Colour::Warning)
                                               << printToString(addLabel("Warning"), labelShift)
                                               << Colour(Colour::None)
                                               << printToString(message, labelShift + this->labelShift);
    }
}

void Printer::notice(const std::string &message, const unsigned int &labelShift) {
    if (enableOutput && (output || errorOutput)) {
        (errorOutput ? *errorOutput : *output) << Colour(Colour::Cyan)
                                               << printToString(addLabel("Note"), labelShift)
                                               << Colour(Colour::None)
                                               << printToString(message, labelShift + this->labelShift);
    }
}

void Printer::print(const std::string &message, const unsigned int &shift) {
    if (enableOutput && output) {
        *output << printToString(message, shift);
    }
}

const std::string Printer::addLabel(const std::string &message) {
    return "[" + message + "]";
}

std::string Printer::printToString(const std::string &message, const unsigned int &shift) {
    std::stringstream os;
    std::stringstream messageStream;
    std::string line;

    messageStream << message;

    while (std::getline(messageStream, line)) {
        os << std::string(shift * shiftMultiplier, ' ') << line << "\n";
    }

    return os.str();
}

std::ostream *Printer::getOutputStream() const {
    return output;
}

void Printer::setOutputStream(std::ostream *stream) {
    Printer::output = stream;
}

std::ostream *Printer::getErrorOutputStream() const {
    return errorOutput;
}

void Printer::setErrorOutputStream(std::ostream *stream) {
    Printer::errorOutput = stream;
}

unsigned int Printer::getShiftMultiplier() const {
    return shiftMultiplier;
}

void Printer::setShiftMultiplier(unsigned int shiftMultiplier) {
    Printer::shiftMultiplier = shiftMultiplier;
}

void Printer::setEnableOutput(bool enableOutput) {
    Printer::enableOutput = enableOutput;
}

bool Printer::isEnableOutput() const {
    return enableOutput;
}
