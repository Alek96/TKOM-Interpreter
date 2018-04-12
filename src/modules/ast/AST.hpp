#ifndef INTERPRETER_AST_HPP
#define INTERPRETER_AST_HPP

namespace tkom {
    class Node {
    public:
        virtual ~Node() {}
        virtual void run() = 0;
    };
}

#endif //INTERPRETER_AST_HPP