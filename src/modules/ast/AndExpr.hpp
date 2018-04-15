#ifndef INTERPRETER_ANDEXPR_HPP
#define INTERPRETER_ANDEXPR_HPP

#include <list>
#include "Expression.hpp"
#include "RelationalExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class RelationalExpr;

        class AndExpr : public Expression {
        public:
            explicit AndExpr(RelationalExpr &&relationalExpr);

            AndExpr(const AndExpr &) = delete;
            AndExpr(AndExpr &&rhs)noexcept;

            Variable calculate() override;

            void addAnd(RelationalExpr &&relationalExpr);

        private:
            std::list<RelationalExpr> relationalExprs;
        };
    }
}


#endif //INTERPRETER_ANDEXPR_HPP
