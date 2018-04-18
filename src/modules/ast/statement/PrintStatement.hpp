#ifndef INTERPRETER_PRINTSTATEMENT_HPP
#define INTERPRETER_PRINTSTATEMENT_HPP

#include <string>
#include <memory>
#include <list>
#include "Statement.hpp"
#include "ast/expression/Expression.hpp"
#include "printer/Printer.hpp"
#include <sstream>

namespace tkom {
    namespace ast {

        class PrintStatement : public Statement {
            enum class Type {
                _Expression,
                _String
            };
        public:
            PrintStatement() = default;

            void addExpression(std::unique_ptr<Expression> expression) {
                types.push_back(Type::_Expression);
                expressions.push_back(std::move(expression));
            }
            void addString(std::string string) {
                types.push_back(Type::_String);
                strings.push_back(std::move(string));
            }

            Return run() override {
                std::stringstream ss;
                auto itExpr = expressions.begin();
                auto itStr = strings.begin();

                for (auto &&type : types) {
                    if(type == Type::_Expression) {
                        ss << itExpr->get()->calculate();
                        ++itExpr;
                    } else {
                        ss << *itStr;
                        ++itStr;
                    }
                }

                Printer::instance().print(ss.str());

                return Return(Return::_none);
            }

        private:
            std::list<Type> types;
            std::list<std::unique_ptr<Expression>> expressions;
            std::list<std::string> strings;
        };

    }
}


#endif //INTERPRETER_PRINTSTATEMENT_HPP
