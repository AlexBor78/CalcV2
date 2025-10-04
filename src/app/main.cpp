#include <iostream>

#include <utils/printast.h>
#include <utils/utils.h>

#include <lexer.h>
#include <parser.h>
#include <compiler.h>
#include <vm.h>

int main()
{
    // Calc::Lexer lexer;
    // auto tokens = lexer.tokenize("10*(100-50)");

    // for(auto tok : tokens)
    // {
    //     Calc::utils::print_token(tok);
    // }

    // parsing
    std::cout << "Start parsing..." << std::endl;
    Calc::Parser parser;
    auto root = parser.parse("10*(100-(-50))");
    std::cout << "Parsing done!" << std::endl;

    // print ast
    Calc::utils::PrintAST printer;
    printer.print(root.get());

    // compiling
    std::cout << "Start compiling..." << std::endl;
    Calc::Compiler compiler;
    auto code = compiler.compile(root.get());
    std::cout << "Done Compiling!" << std::endl;

    // print bytecode
    for(auto instruct : code)
    {
        Calc::utils::print_instruct(instruct);
    }

    // executing
    std::cout << "Start executing..." << std::endl;
    Calc::VM vm;
    auto result = vm.exec(code);
    std::cout << "Executing Done! Result: " << result << std::endl;
}
