#include "Library.hpp"

using namespace tkom;

Library::Library(Parser &parser) : parser(parser) {
    addConvertFrom2dTo3d();
    addConvertFrom3dTo2d();
    addCrossProduct();
    addScalarProduct();
}

void Library::addConvertFrom2dTo3d() {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    parser.setLexer(std::make_unique<tkom::Lexer>(stream));
    stream << "function convertFrom2dTo3d(vec2d) {\n"
              "var res=vec(1,2,3);"
              "res[0]=vec2d[0];\n"
              "res[1]=vec2d[1];\n"
              "res[2]=0;\n"
              "return res;\n"
              "}\n";
    parser.parse();
    parser.clearLexer();
}

void Library::addConvertFrom3dTo2d() {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    parser.setLexer(std::make_unique<tkom::Lexer>(stream));
    stream << "function convertFrom3dTo2d(vec3d) {\n"
              "var res=vec(1,2);"
              "res[0]=vec3d[0];\n"
              "res[1]=vec3d[1];\n"
              "return res;\n"
              "}\n";
    parser.parse();
    parser.clearLexer();
}

void Library::addCrossProduct() {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    parser.setLexer(std::make_unique<tkom::Lexer>(stream));
    stream << "function crossProduct2(vec1, vec2) {\n"
              "var res=vec(1,2);"
              "res[0]=vec1[1] - vec2[1];\n"
              "res[1]=vec2[0] - vec1[0];\n"
              "return res;\n"
              "}\n";
    stream << "function crossProduct3(vec1, vec2) {\n"
              "var res=vec(1,2,3);"
              "res[0]=vec1[1]*vec2[2] - vec1[2]*vec2[1];\n"
              "res[1]=vec1[2]*vec2[0] - vec1[0]*vec2[2];\n"
              "res[2]=vec1[0]*vec2[1] - vec1[1]*vec2[0];\n"
              "return res;\n"
              "}\n";
    parser.parse();
    parser.clearLexer();
}

void Library::addScalarProduct() {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    parser.setLexer(std::make_unique<tkom::Lexer>(stream));
    stream << "function scalarProduct2(vec1, vec2) {\n"
              "var res = vec1[0]*vec2[0] + vec1[1]*vec2[1];\n"
              "return res;\n"
              "}\n";
    stream << "function scalarProduct3(vec1, vec2) {\n"
              "var res = vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];\n"
              "return res;\n"
              "}\n";
    parser.parse();
    parser.clearLexer();
}
