#include <iostream>
#include <cctype>
#include <compile/lexer.h>
#include <stdexcept>

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
            if(is_num())
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
            next(1);
        }
        tokens.emplace_back(types::TokenType::END);
        return tokens;
    }

    char Lexer::curr() const noexcept
    {
        if(pos < input.size())
        {
            return input[pos];
        }
        return 0;
    }
    char Lexer::peak(int offset=1) const noexcept
    {
        if(pos + offset < input.size())
        {
            return input[pos + offset];
        }
        return 0;
    }
    char Lexer::next(int offset=1) noexcept
    {
        pos+=offset;
        if(pos < input.size())
        {
            return input[pos];
        }
        return 0;
    }

    bool Lexer::is_punct() noexcept
    {
        return curr() == '+'
        || curr() == '-'
        || curr() == '*'
        || curr() == '/'
        || curr() == '('
        || curr() == ')';
    }
    bool Lexer::is_num() noexcept
    {
        return isdigit(curr()) || curr() == '.';
    }

    void Lexer::add_token(types::Token tok) noexcept
    {
        tokens.emplace_back(tok);
    }
    void Lexer::add_token(types::TokenType tok) noexcept
    {
        tokens.emplace_back(tok, nullptr);
    }
    void Lexer::add_token(types::TokenType tok, const char ch) noexcept
    {
        tokens.emplace_back(tok, std::string(1, ch));
    }
    void Lexer::add_token(types::TokenType tok, const char* ch) noexcept
    {
        tokens.emplace_back(tok, ch);
    }

    void Lexer::skip_spaces() noexcept
    {
        while (pos < input.size() && isspace(curr()))
        {
            next();
        }
    }
    void Lexer::tokenize_number()
    {
        std::string buf("");
        bool has_dot{false};
        while (pos < input.size()
        &&  (isdigit(curr()) || (!has_dot && curr() == '.'))
        ){
            if(isdigit(curr()))
            {
                buf += curr();
                next();
                continue;
            }
            if(curr() == '.')
            {
                if(has_dot)
                {
                    throw std::runtime_error("bad number: " + buf + curr());
                }
                if(buf.empty())
                {
                    buf+='0';
                }
                has_dot = true;
                buf += curr();
                next();
            }
        }
        add_token(types::TokenType::NUMBER, buf.c_str());
    }
    void Lexer::tokenize_punct() noexcept
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
