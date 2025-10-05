#include <iostream>

#include <utils/printast.h>
#include <utils/utils.h>

#include <compile/lexer.h>
#include <compile/parser.h>
#include <compile/compiler.h>
#include <compile/typechecker.h>
#include <runtime/vm.h>

int main()
{
    // Calc::Lexer lexer;
    // auto tokens = lexer.tokenize("10*(100-50)");

    // for(auto tok : tokens)
    // {
    //     Calc::utils::print_token(tok);
    // }

    // std::string expr("(100-10*3)+(10-100*(30/15))");
    std::string expr("10*(100-(-50))");

    std::cout << "Expr: " << expr << std::endl;

    // parsing
    std::cout << "Start parsing..." << std::endl;
    std::cout << "Creating AST..." << std::endl;
    Calc::Parser parser;
    auto root = parser.parse(expr);
    // todo:
    // std::cout << "Check for types..." << std::endl;
    // Calc::compile::TypeChecker checker(parser.get_typetable());
    // checker.check(root.get());

    std::cout << "Parsing done!" << std::endl;

    // print ast
    std::cout << std::endl;
    Calc::utils::PrintAST printer;
    printer.print(root.get());
    std::cout << std::endl;

    // compiling
    std::cout << "Start compiling..." << std::endl;
    Calc::Compiler compiler;
    auto code = compiler.compile(root.get());
    std::cout << "Done Compiling!" << std::endl;

    // print bytecode
    std::cout << std::endl;
    for(const auto& instruct : code)
    {
        Calc::utils::print_instruct(instruct);
    }
    std::cout << std::endl;

    // executing
    std::cout << "Start executing..." << std::endl;
    Calc::VM vm;
    auto result = vm.exec(code);
    std::cout << "Result: " << std::endl;
    Calc::utils::print_value(result);
}
