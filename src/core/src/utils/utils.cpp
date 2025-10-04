#include <iostream>
#include <utils/utils.h>

namespace Calc::utils
{
    void print_token(Calc::types::Token tok)
    {
        switch (tok.tt)
        {
            case(Calc::types::TokenType::PLUS):
                std::cout << "Token: PLUS" << std::endl;
                break;

            case(Calc::types::TokenType::MINUS):
                std::cout << "Token: MINUS" << std::endl;
                break;

            case(Calc::types::TokenType::MUL):
                std::cout << "Token: MUL" << std::endl;
                break;

            case(Calc::types::TokenType::DIV):
                std::cout << "Token: DIV" << std::endl;
                break;

            case(Calc::types::TokenType::NUMBER):
                std::cout << "Token: NUMBER" << std::endl;
                break;

            case(Calc::types::TokenType::END):
                std::cout << "Token: END" << std::endl;
                break;
                
            case(Calc::types::TokenType::LEFT_BRACKET):
                std::cout << "Token: LEFT_BRACKET" << std::endl;
                break;

            case(Calc::types::TokenType::RIGHT_BRACKET):
                std::cout << "Token: RIGHT_BRACKET" << std::endl;
                break;
        }
        std::cout << "Symbol: " << tok.sym << std::endl;
    }

    void print_instruct(Calc::types::Instruction instruct)
    {
        switch (instruct.op)
        {
            case(Calc::types::OpCode::PUSH):
                std::cout << "PUSH " << instruct.operand << std::endl;
                return;

            case(Calc::types::OpCode::ADD):
                std::cout << "ADD " << std::endl;
                return;

            case(Calc::types::OpCode::SUB):
                std::cout << "SUB " << std::endl;
                return;

            case(Calc::types::OpCode::MUL):
                std::cout << "MUL " << std::endl;
                return;

            case(Calc::types::OpCode::DIV):
                std::cout << "DIV " << std::endl;
                return;

            case(Calc::types::OpCode::INVERSE):
                std::cout << "INVERSE " << std::endl;
                return;
        }
    }
}
