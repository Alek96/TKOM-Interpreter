#ifndef INTERPRETER_RETURNSTATEMENT_HPP
#define INTERPRETER_RETURNSTATEMENT_HPP

#include "modules/ast/Statement.hpp"
#include "StatementBlock.hpp"

namespace tkom { namespace ast {

        class ReturnStatement : public Statement {

        private:
            StatementBlock block;
            //LogicExpr
        };

}    }

#endif //INTERPRETER_RETURNSTATEMENT_HPP
