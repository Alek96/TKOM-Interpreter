#ifndef INTERPRETER_LIBRARY_HPP
#define INTERPRETER_LIBRARY_HPP

#include "parser/Parser.hpp"

namespace tkom {
    class Library {
    public:
        explicit Library(Parser& parser);

    private:
        Parser& parser;
        void addConvertFrom2dTo3d();
        void addConvertFrom3dTo2d();
        void addCrossProduct();
        void addScalarProduct();
    };

}


#endif //INTERPRETER_LIBRARY_HPP
