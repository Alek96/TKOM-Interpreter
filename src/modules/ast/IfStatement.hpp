#ifndef INTERPRETER_IFSTATEMENT_HPP
#define INTERPRETER_IFSTATEMENT_HPP

#include "modules/ast/Statement.hpp"
#include "StatementBlock.hpp"

namespace tkom { namespace ast {

    class IfStatement : public StatementBlock {

        virtual ~IfStatement() {
            delete ifBlock;
            delete elseBlock;
        }
        void run() override {
            if (logicExpr) {
                ifBlock->run();
            } else {
                elseBlock->run();
            }
        }

    private:
        StatementBlock* ifBlock = nullptr;
        StatementBlock* elseBlock = nullptr;
        //LogicExpr
        bool logicExpr = true;
    };

}}


#endif //INTERPRETER_IFSTATEMENT_HPP
