#include "ast.h"
#include <iostream>
#include <lexer.h>
#include <memory>
#include <print_visitor.h>

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
    }
    std::cout << "Symbol: " << tok.sym << std::endl;
}

int main()
{
    Lexer lexer;

    // auto tokens = lexer.tokenize("5+1-3+4");

    // for(auto tok : tokens)
    // {
    //     print_token(tok);
    // }

    auto root = std::make_unique<BinOp>(
        BinOp::BinOpKind::PLUS,
        std::make_unique<Number>(5),
        std::make_unique<BinOp>(
            BinOp::BinOpKind::MUL,
            std::make_unique<Number>(5),
            std::make_unique<Number>(5)
        )
    );

    PrintAST printer;
    printer.print(root.get());

}
