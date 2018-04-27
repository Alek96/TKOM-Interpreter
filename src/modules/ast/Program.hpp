#ifndef INTERPRETER_PROGRAM_HPP
#define INTERPRETER_PROGRAM_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include "modules/ast/statement/Statement.hpp"
#include "FunctionDef.hpp"
#include "exception/Exception.hpp"

namespace tkom {
    namespace ast {

        class Program {
        public:
            Program() = default;

            void addFunction(std::unique_ptr<FunctionDef> function) {
                functions.insert({function->getIdentifier(), std::move(function)});
            }

            FunctionDef &findFunction(std::string &identifier) {
                return *functions.at(identifier);
            }

            void eraseFunction(const std::string &identifier) {
                functions.erase(identifier);
            }

            const bool existFunction(const std::string &identifier) const {
                return functions.count(identifier);
            }

            Return run() {
                for (auto &&function : functions) {
                    if (function.second->getIdentifier() == "main") {
                        return function.second->run();
                    }
                }
                throw Exception("Program doesn't contain main function");
            };

        private:
            std::unordered_map<std::string, std::unique_ptr<FunctionDef>> functions;
        };
    }
}

#endif //INTERPRETER_PROGRAM_HPP
