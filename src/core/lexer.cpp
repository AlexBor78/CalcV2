#include <iostream>
#include <cctype>
#include <lexer.h>

std::vector<Token> Lexer::tokenize(const std::string& _input)
{
    for(const auto& ch : _input)
    {
        if(isspace(ch))
        {
            continue;
        }
        switch (ch)
        {
            case('+'):
                tokens.push_back({TokenType::PLUS, ch});
                continue;

            case('-'):
                tokens.push_back({TokenType::PLUS, ch});
                continue;

            case('*'):
                tokens.push_back({TokenType::MUL, ch});
                continue;

            case('/'):
                tokens.push_back({TokenType::DIV, ch});
                continue;

            case('0'): case('1'): case('2'): case('3'): case('4'):
            case('5'): case('6'): case('7'): case('8'): case('9'):
                tokens.push_back({TokenType::NUMBER, ch});
                continue;
            default:
                std::cerr << "Unknow token: " << ch << std::endl;
                break;
        }
    }
    tokens.push_back({TokenType::END});
    return tokens;
}
