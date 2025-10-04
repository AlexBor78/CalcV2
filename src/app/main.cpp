#include "defs.h"
#include <iostream>
#include <print_visitor.h>

#include <lexer.h>
#include <parser.h>
#include <compiler.h>
#include <vm.h>

void print_token(Token tok)
{
    switch (tok.tt)
    {
        case(TokenType::PLUS):
            std::cout << "Token: PLUS" << std::endl;
            break;

        case(TokenType::MINUS):
            std::cout << "Token: MINUS" << std::endl;
            break;

        case(TokenType::MUL):
            std::cout << "Token: MUL" << std::endl;
            break;

        case(TokenType::DIV):
            std::cout << "Token: DIV" << std::endl;
            break;

        case(TokenType::NUMBER):
            std::cout << "Token: NUMBER" << std::endl;
            break;

        case(TokenType::END):
            std::cout << "Token: END" << std::endl;
            break;
            
        case(TokenType::LEFT_BRACKET):
            std::cout << "Token: LEFT_BRACKET" << std::endl;
            break;

        case(TokenType::RIGHT_BRACKET):
            std::cout << "Token: RIGHT_BRACKET" << std::endl;
            break;
    }
    std::cout << "Symbol: " << tok.sym << std::endl;
}

void print_instruct(Instruction instruct)
{
    switch (instruct.op)
    {
        case(OpCode::PUSH):
            std::cout << "PUSH " << instruct.operand << std::endl;
            return;

        case(OpCode::ADD):
            std::cout << "ADD " << std::endl;
            return;

        case(OpCode::SUB):
            std::cout << "SUB " << std::endl;
            return;

        case(OpCode::MUL):
            std::cout << "MUL " << std::endl;
            return;

        case(OpCode::DIV):
            std::cout << "DIV " << std::endl;
            return;

        case(OpCode::INVERSE):
            std::cout << "INVERSE " << std::endl;
            return;
    }
}

int main()
{
    // Lexer lexer;
    // auto tokens = lexer.tokenize("10*(100-50)");

    // for(auto tok : tokens)
    // {
    //     print_token(tok);
    // }

    // parsing
    std::cout << "Start parsing..." << std::endl;
    Parser parser;
    auto root = parser.parse("10*(100-(-50))");
    std::cout << "Parsing done!" << std::endl;

    // print ast
    PrintAST printer;
    printer.print(root.get());

    // compiling
    std::cout << "Start compiling..." << std::endl;
    Compiler compiler;
    auto code = compiler.compile(root.get());
    std::cout << "Done Compiling!" << std::endl;

    // print bytecode
    for(auto instruct : code)
    {
        print_instruct(instruct);
    }

    // executing
    std::cout << "Start executing..." << std::endl;
    VM vm;
    auto result = vm.exec(code);
    std::cout << "Executing Done! Result: " << result << std::endl;
}
