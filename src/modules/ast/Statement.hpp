#ifndef INTERPRETER_AST_HPP
#define INTERPRETER_AST_HPP

namespace tkom {
    class Statement {
    public:
        virtual ~Statement() = default;
        virtual void run() = 0;
    };
}

#endif //INTERPRETER_AST_HPP