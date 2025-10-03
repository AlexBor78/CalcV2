#include <iostream>
#include <print_visitor.h>
#include <parser.h>

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
    std::cout << "Start parsing!" << std::endl;
    
    Parser parser;
    auto root = parser.parse("5*3+5*3");

    std::cout << "Parsing done!" << std::endl;

    PrintAST printer;
    printer.print(root.get());

}
