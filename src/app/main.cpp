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
    // auto tokens = lexer.tokenize("1 1.5 0.5 .10");

    // for(auto tok : tokens)
    // {
    //     Calc::utils::print_token(tok);
    // }
    // return 0;

    // std::string expr("(100-10*3)+(10-100*(30/15))");
    std::string expr("10*(100-(-50)) + +.52");
    std::cout << "Expr: " << expr << std::endl << std::endl;

    std::cout << "Start compilation!" << std::endl;

    // ast
    std::cout << "Creating AST...";
    Calc::Parser parser;
    auto root = parser.parse(expr);
    std::cout << " done!" << std::endl;

    std::cout << "Check for types...";
    Calc::compile::TypeChecker checker(parser.get_typetable());
    checker.check(root.get());
    std::cout << " done!" << std::endl;

    // print ast
    std::cout << std::endl;
    Calc::utils::PrintAST printer;
    printer.print(root.get());
    std::cout << std::endl;

    // compiling
    std::cout << "Generating bytecode...";
    Calc::Compiler compiler;
    auto code = compiler.compile(root.get());
    std::cout << " done!" << std::endl;

    std::cout << "Compilation done!" << std::endl;

    // print bytecode
    std::cout << std::endl;
    for(const auto& instruct : code)
    {
        Calc::utils::print_instruct(instruct);
    }
    std::cout << std::endl;

    // executing
    std::cout << "Start executing...";
    Calc::VM vm;
    auto result = vm.exec(code);
    std::cout << " done!" << std::endl;
    std::cout << "Result: " << std::endl;
    Calc::utils::print_value(result);
}
