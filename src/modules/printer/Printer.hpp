#ifndef INTERPRETER_TERMINALPRINTER_HPP
#define INTERPRETER_TERMINALPRINTER_HPP

#include <string>
#include <ostream>

namespace tkom {
    class Printer {
    private:
        explicit Printer();
    public:
        void error(const std::string& message, const unsigned int& labelShift = 0);
        void warning(const std::string& message, const unsigned int& labelShift = 0);
        void notice(const std::string& message, const unsigned int& labelShift = 0);
        void print(const std::string& message, const unsigned int& shift = 0);

        static Printer& instance() {
            static Printer s_instance;
            return s_instance;
        }

        std::ostream *getOutputStream() const;
        void setOutputStream(std::ostream *stream);
        std::ostream *getErrorOutputStream() const;
        void setErrorOutputStream(std::ostream *stream);

        unsigned int getShiftMultiplier() const;
        void setShiftMultiplier(unsigned int shiftMultiplier);
        void setEnableOutput(bool enableOutput);
        bool isEnableOutput() const;

    private:
        std::ostream* output;
        std::ostream* errorOutput;
        unsigned int shiftMultiplier;
        unsigned int labelShift;
        bool enableOutput = false;

        const std::string addLabel(const std::string& message);
        std::string printToString(const std::string &message, const unsigned int &shift = 0);
    };
}

#endif //INTERPRETER_TERMINALPRINTER_HPP
