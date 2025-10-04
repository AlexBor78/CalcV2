#include <iostream>
#include <cctype>
#include <compile/lexer.h>

namespace Calc
{
    std::vector<types::Token> Lexer::tokenize(const std::string& _input)
    {
        input = _input;
        pos = 0;
        while(pos < input.size())
        {
            if(isspace(curr()))
            {
                skip_spaces();
            }

            if(isdigit(curr()))
            {
                tokenize_number();
                continue;
            }

            if(is_punct())
            {
                tokenize_punct();
                continue;
            }
            std::cerr << "Bad token: " << curr() << std::endl;
        }
        tokens.push_back({types::TokenType::END});
        return tokens;
    }

    char Lexer::curr()
    {
        if(pos < input.size())
        {
            return input[pos];
        }
        return 0;
    }
    char Lexer::peak(int offset=1)
    {
        if(pos + offset < input.size())
        {
            return input[pos + offset];
        }
        return 0;
    }
    char Lexer::next(int offset=1)
    {
        pos+=offset;
        if(pos < input.size())
        {
            return input[pos];
        }
        return 0;
    }

    bool Lexer::is_punct()
    {
        return curr() == '+'
        || curr() == '-'
        || curr() == '*'
        || curr() == '/'
        || curr() == '('
        || curr() == ')';
    }

    void Lexer::add_token(types::Token tok)
    {
        tokens.push_back(tok);
    }
    void Lexer::add_token(types::TokenType tok)
    {
        tokens.push_back({tok, nullptr});
    }
    void Lexer::add_token(types::TokenType tok, const char ch)
    {
        tokens.push_back({tok, std::string(1, ch)});
    }
    void Lexer::add_token(types::TokenType tok, const char* ch)
    {
        tokens.push_back({tok, ch});
    }

    void Lexer::skip_spaces()
    {
        while (pos < input.size() && isspace(curr()))
        {
            next();
        }
    }
    void Lexer::tokenize_number()
    {
        std::string buf("");
        while (pos < input.size() && isdigit(curr()))
        {
            buf += curr();
            next();
        }
        add_token(types::TokenType::NUMBER, buf.c_str());
    }
    void Lexer::tokenize_punct()
    {
        auto ch = curr(); 
        next();
        switch (ch)
        {
            case('+'):
                add_token(types::TokenType::PLUS, ch);
                return;

            case('-'):
                add_token(types::TokenType::MINUS, ch);
                return;

            case('*'):
                add_token(types::TokenType::MUL, ch);
                return;

            case('/'):
                add_token(types::TokenType::DIV, ch);
                return;

            case('('):
                add_token(types::TokenType::LEFT_BRACKET, ch);
                return;

            case(')'):
                add_token(types::TokenType::RIGHT_BRACKET, ch);
                return;
            default:
                std::cerr << "Unknow operator: " << ch << std::endl;
        }
    }
}
