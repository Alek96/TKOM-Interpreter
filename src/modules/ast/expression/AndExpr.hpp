#ifndef INTERPRETER_ANDEXPR_HPP
#define INTERPRETER_ANDEXPR_HPP

#include <list>
#include "Expression.hpp"
#include "RelationalExpr.hpp"
#include "modules/Token/Token.hpp"

namespace tkom {
    namespace ast {

        class AndExpr : public Expression {
            using exprPtr = std::unique_ptr<Expression>;

        public:
            explicit AndExpr(exprPtr relationalExpr);

            AndExpr(const AndExpr &) = delete;
            AndExpr(AndExpr &&rhs)noexcept;

            Variable calculate() const override;

            void addAnd(exprPtr relationalExpr);

        private:
            std::list<exprPtr> relationalExprs;
        };
    }
}


#endif //INTERPRETER_ANDEXPR_HPP
